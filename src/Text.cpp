#include <QOpenGLFunctions>

#include <stdio.h>		// for fopen()...
#include <string.h>		// for strncpy()
#include <iostream>		// for cerr

#include "WinInfo.h"
#include "Time.h"
#include "Text.h"

typedef enum {
  FILE_BLENDIN,
  FILE_BLENDOUT,
  FILE_SHOW,
  FILE_DONTSHOW
} textState;

// global
// ------

// the file we have to draw - if set to nullptr, the file
// could not be opened and therefore a corresponding message should be shown
static FILE *file;

// the name of the current file which is opened to be drawn
char curFileName[MAX_FILENAME_LEN];

// the time it takes to blend the help text in and out [in ms]
static GLdouble blendInTime, blendOutTime;

// the current state of the delay bar
static textState state;

// the time the delayBar has been in a certain state [in ms]
static GLdouble stateTime;

// the alpha (scaling) value, in [0.0, 1.0]
static GLdouble alpha;

static void *curFont;

// local
// -----

// returns a pointer to the next line of the textfile given by global 'fd'. It returns
// nullptr either if the end of the text file has been reached. 'file' must be a valid
// file stream
static char *getNextLine (void) {
	
  static char line[MAX_LINE_LEN];
  int i;
  // the character just read
  int ch; 
	
  ch = EOF;
	
  for (i = 0; (i < MAX_LINE_LEN - 1) && ((ch = fgetc (file)) != EOF) && (ch != '\n'); i++) {
    line[i] = (char) ch;
  }
	
  line[i] = '\0';
	
  // did we reach the end of the file
  if (ch != EOF) {
    return &line[0];
  }
  else {
    return nullptr;
  }
	
}  // getNextLine()


// draws the text file
static void draw (void) {
	
  char *line;
  GLdouble offset;

  // set GL switches to custom values
  glDisable (GL_DEPTH_TEST);
  glEnable (GL_BLEND);

  glMatrixMode (GL_PROJECTION);
  // make backup of current projection matrix
  glPushMatrix(); 
  glLoadIdentity();
  glOrtho(0.0, (GLdouble) wininfo.width, 0.0, (GLdouble) wininfo.height, -1, 1);

  glMatrixMode (GL_MODELVIEW);
  // make backup of current modelview matrix
  glPushMatrix();
  glLoadIdentity();
	
  // draw background
  glBegin (GL_QUADS);
	
  glColor4d (0.20, 0.3, 0.20, alpha * 0.75);
  glVertex2d ((GLdouble) wininfo.width * 0.025, (GLdouble) wininfo.height * 0.2);
  glVertex2d ((GLdouble) wininfo.width * 0.975, (GLdouble) wininfo.height * 0.2);
  glVertex2d ((GLdouble) wininfo.width * 0.975, (GLdouble) wininfo.height * 0.8);
  glVertex2d ((GLdouble) wininfo.width * 0.025, (GLdouble) wininfo.height * 0.8);
	
  glEnd();

  // draw frame
  glBegin (GL_LINE_LOOP);
	
  glColor4d (0.0, 1.0, 0.0, alpha * 1.0);
  glVertex2d ((GLdouble) wininfo.width * 0.025, (GLdouble) wininfo.height * 0.2);
  glVertex2d ((GLdouble) wininfo.width * 0.975, (GLdouble) wininfo.height * 0.2);
  glVertex2d ((GLdouble) wininfo.width * 0.975, (GLdouble) wininfo.height * 0.8);
  glVertex2d ((GLdouble) wininfo.width * 0.025, (GLdouble) wininfo.height * 0.8);
	
  glEnd();

  glMatrixMode (GL_PROJECTION);
  // restore current projection matrix
  glPopMatrix();
  glMatrixMode (GL_MODELVIEW);
  // restore current modelview matrix
  glPopMatrix();

  // reset GL switches to default values
  glDisable (GL_BLEND);
  glEnable (GL_DEPTH_TEST);
	
  // set text font
  // TODO Replace font rendering
  //setTextFont (GLUT_BITMAP_9_BY_15);
	
  offset = 0.0;
  if (file != nullptr) {
		
    line = getNextLine();    
    while (line != nullptr) {
			
      writeText (line, 0.05 * (GLdouble) wininfo.width, 0.75 * (GLdouble) wininfo.height - offset, (GLdouble) alpha);
      offset += 16.0;
      line = getNextLine();
			
    }
		
    // rewind the file for the next drawing
    rewind (file);
		
  }
  else {

    writeText (curFileName, 0.05 * (GLdouble) wininfo.width, 0.7 * (GLdouble) wininfo.height - offset, (GLdouble) alpha);
    offset += 16.0;
    writeText ("Die Datei konnte nicht gefunden werden!", 0.15 * (GLdouble) wininfo.width, 0.7 * (GLdouble) wininfo.height - offset, (GLdouble) alpha);
		
  }
  
}  // draw()

// public
// ------

void setTextFont (void *font) {
  curFont = font;
}

void *getTextFont (void) {
  return curFont;
}

void writeText (const char *string, const GLdouble x, const GLdouble y, const GLdouble alpha) {

  int len, i;


#if 1 
  glMatrixMode (GL_PROJECTION);
  // make backup of current projection matrix
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, (GLdouble) wininfo.width, 0.0, (GLdouble) wininfo.height, -1, 1);

#endif

  glMatrixMode (GL_MODELVIEW);
  // make backup of current modelview matrix
  glPushMatrix();
  glLoadIdentity();

  // set GL switches to custom values
  glEnable (GL_BLEND);

  glColor4d (0.0, 1.0, 0.0, alpha);

  glRasterPos2f (x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    // TODO REPLACE text rendering
    // glutBitmapCharacter(curFont, string[i]);
  }

  // set GL switches to default values
  glDisable (GL_BLEND);

#if 1
  glMatrixMode (GL_PROJECTION);
  
  glPopMatrix();
#endif
  glMatrixMode (GL_MODELVIEW);
  // restore current modelview matrix
  glPopMatrix();
}

void initTextFile(void) {
	
  state = FILE_DONTSHOW;
  stateTime = 0.0;
  blendInTime = 500;
  blendOutTime = 500;
	
  // set terminating '\0' at the end of the file name
  curFileName[MAX_FILENAME_LEN - 1] = '\0';
	
}  // initTextFile

void drawTextFile (void) {
  
  // set text font
  // TODO Replace font rendering
  // setTextFont (GLUT_BITMAP_8_BY_13);
	
  switch (state) {
		
  case FILE_DONTSHOW:
    {
      return;
    }
    break;
		
  case FILE_SHOW:
    {
      draw();
    }
    break;
		
  case FILE_BLENDIN:
    {
      alpha = stateTime / blendInTime;
      if (stateTime > blendInTime) {
				// state change
	state = FILE_SHOW;
	stateTime = 0.0;
	alpha = 1.0;
      }
      draw();
    }
    break;
		
  case (FILE_BLENDOUT):
    {
			
      if (stateTime > blendOutTime) {
	
	// state change
	state = FILE_DONTSHOW;
	stateTime = 0.0;
	alpha = 0.0;
				
	// CLOSE the file
	if (file != nullptr) {
	  fclose (file);
	}
	file = nullptr;
	curFileName[0] = '\0';

      }
      else {
	alpha = 1.0 - stateTime / blendOutTime;
	draw();
      }
    }
    break;
		
  }   
	
  // update the current state time
  stateTime += dt;
	
}  // drawTextFile

void toggleTextFile (const char *fileName) {
	
  switch (state) {
		
  case FILE_DONTSHOW:
    {
      state = FILE_BLENDIN;
      stateTime = 0.0;
			
      // OPEN the file
      // note: no error checking here, since the error is catched
      // later on in case 'file' is set to nullptr
      file = fopen (fileName, "r");
      strncpy (curFileName, fileName, MAX_FILENAME_LEN - 1); 
			
    }
    break;
		
  case FILE_SHOW:
    {
      state = FILE_BLENDOUT;
      stateTime = 0.0;
    }
    break;
		
  case FILE_BLENDOUT:
    {
      state = FILE_BLENDIN;
      stateTime = 0.0;
    }
    break;
		
  case FILE_BLENDIN:
    {
      state = FILE_BLENDOUT;
      stateTime = 0.0;
    }
    break;
		
  }  // switch (state)
	
}  // toggleTextFile

void changeTextFile (const char *fileName) {
  
  // only change text file if there is one currently showing
  if (file != nullptr) {
    fclose (file);
    file = fopen (fileName, "r");
    strncpy (curFileName, fileName, MAX_FILENAME_LEN - 1);
  }

}
  

  
