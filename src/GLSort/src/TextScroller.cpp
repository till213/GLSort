#include <QOpenGLFunctions>
#include <string.h>	// for strcpy()

#include "Text.h"
#include "Timer.h"
#include "WinInfo.h"
#include "TextScroller.h"

#define NLINES		4
// there is no way to get the height of a (GLUT) font, or is there?
#define TEXTHEIGHT	18.0

// typedefs
// --------

// the state of the delay bar
typedef enum {
  LINE_SHOW,
  LINE_BLENDOUT,  
  LINE_DONTSHOW
} LineState;

typedef struct {
  // text of the line
  Message text;
  // the state
  LineState state;
  // the time this line has been in 'state' [in ms]
  GLdouble stateTime;
} Line;

// global
// ------

// the time it takes to blend out, and the time after which a line is scrolled up [in ms]
static GLdouble showTime, blendOutTime;

// the number of lines showing
int nShow;

// the number of lines blending out
int nBlendOut;

// the next line where the next text line will be inserted - if line 0 and 1
// are occupied by a text (which is constantly showing, i.e. not fading out)
// then 'nextLine' will be 2
static int nextLine;

static Line lines[NLINES];

// local
// -----

static void scroll (void) {

  int i;

  for (i = 1; i < nShow; i++) {

    strcpy ((char *) lines[i-1].text, (char *) lines[i].text);
    if (lines[i].stateTime > showTime - blendOutTime) {
      lines[i-1].stateTime = showTime - blendOutTime;
    }
    else {
      lines[i-1].stateTime = lines[i].stateTime - blendOutTime; 
    }
  
  }  // for (i)  
  
  // blend out the last line which was showing
  lines[nShow - 1].state = LINE_BLENDOUT;
  lines[nShow - 1].stateTime = 0.0;
  nBlendOut++;
  nShow--;
  
  nextLine--;
  
} // scroll()

static void checkStates (void) {

  int i;

  // check if there are any visible lines and
  // if we have to scroll
  if (nShow > 0) {
    if ((lines[0].state == LINE_SHOW) && (lines[0].stateTime > showTime)) {
      scroll();
    }
  }
 
  for (i = 0; i < nShow + nBlendOut; i++) {

    switch (lines[i].state) {

    case LINE_SHOW:
      {	
	lines[i].stateTime += dt;
      }
      break;

    case LINE_BLENDOUT:
      {

	if (lines[i].stateTime < blendOutTime) {
	  lines[i].stateTime += dt;
	}
	else {
	  lines[i].state = LINE_DONTSHOW;
	  nBlendOut--;
	}

      }
      break;

    default:
      break;

    }

  }  // while (i < nShow + nBlendOut)


} // checkStates()

// public
// ------

void initTextScroller (void) {

  int i;

  showTime = 5000.0;
  blendOutTime = 1000.0;
  nShow = 0;
  nBlendOut = 0;
  nextLine = 0;

  for (i = 0; i < NLINES; i++) {
    lines[i].state = LINE_DONTSHOW;
  }

}  // initWriteLine()

void writeScrollerLine (const Message text) {

  // is there still a line free?
  if (nextLine == NLINES) {
    // no, so scroll every line by one line up
    scroll();
  }

  switch (lines[nextLine].state) {
    
  case LINE_DONTSHOW:
    {
      nShow++;
    }
    break;

  case LINE_BLENDOUT:
    {
      nShow++;
      nBlendOut--;
    }
    break;

  default:
    break;
 
  }  // switch (lines[nextLine].state)

  // init the new line
  strcpy ((char *) lines[nextLine].text, (char *) text);
  
  lines[nextLine].state = LINE_SHOW;
  lines[nextLine].stateTime = 0.0;
  nextLine++;

}  // writeScrollerLine()

void drawTextScroller (void) {

  int i;
  GLdouble xStart, yStart;
  GLdouble lineWidth;

  // set text font
  // TODO Replace text rendering
  // setTextFont (GLUT_BITMAP_9_BY_15);

  // lineWidth = (GLdouble) MAX_MSG_LEN * glutBitmapWidth (getTextFont(), (int) ' ');
  xStart = ((GLdouble) wininfo.width - lineWidth) / 2.0;
  yStart = (GLdouble) wininfo.height * 0.9;

  checkStates();

  for (i = 0; i < nShow + nBlendOut; i++) {

    switch (lines[i].state) {

    case LINE_SHOW:
      { 
	writeText ((char *) lines[i].text, xStart, yStart - (GLdouble) i * TEXTHEIGHT, 1.0);
      }
      break;

    case LINE_BLENDOUT:
      { 
	writeText ((char *) lines[i].text, xStart, yStart - (GLdouble) i * TEXTHEIGHT, 1.0 - (GLdouble) (lines[i].stateTime / blendOutTime));
      }
      break;

    default:
      break;

    }  // switch (state)

  }  // for (i)

}
	
