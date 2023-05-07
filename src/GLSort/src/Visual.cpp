#include <QOpenGLFunctions>

#include "Array.h"
#include "DelayBar.h"
#include "Text.h"
#include "TextScroller.h"

static void drawAxes (const GLdouble size) {

  GLdouble size_2;

  size_2 = size / 2.0;

  glBegin (GL_LINES);

  glColor3d (1.0, 0.0, 0.0);
  glVertex3d (-size_2, 0.0, -1.0);
  glVertex3d ( size_2, 0.0, -1.0);

  glVertex3d (-size_2, size_2, -1.0);
  glVertex3d ( size_2, size_2, -1.0);
  
  glVertex3d (-size_2, size, -1.0);
  glVertex3d ( size_2, size, -1.0);

  glVertex3d (-size_2, 0.0, -1.0);
  glVertex3d (-size_2, size, -1.0);

  glVertex3d (size_2, 0.0, -1.0);
  glVertex3d (size_2, size, -1.0);

  glEnd();

}
  
static void drawBox (const GLdouble size) {

  GLdouble corner, step, bottom, top;
  const int nlines = 7;
  int i;

  corner = size * 1.5;
  bottom = -size;
  top    = 2.0 * size;
  step = corner * 2.0 / (GLdouble) (nlines - 1);

  glEnable (GL_BLEND);
  
  for (i = 0; i < nlines; i++) {
  
    glBegin (GL_LINE_LOOP);

    glColor4d (0.0, 1.0, 1.0, 0.15);  
    glVertex3d (-corner, bottom, -corner + (GLdouble) i * step);
    glVertex3d (-corner, top, -corner + (GLdouble) i * step);
    glVertex3d ( corner, top, -corner + (GLdouble) i * step);
    glVertex3d ( corner, bottom, -corner + (GLdouble) i * step); 

    glEnd();

    glBegin (GL_LINE_LOOP);
    glVertex3d (-corner + (GLdouble) i * step, bottom, -corner);
    glVertex3d (-corner + (GLdouble) i * step, top, -corner);
    glVertex3d (-corner + (GLdouble) i * step, top, corner);
    glVertex3d (-corner + (GLdouble) i * step, bottom, corner); 

    glEnd();

    glBegin (GL_LINE_LOOP);
  
    glVertex3d (-corner, bottom  + (GLdouble) i * step, -corner);
    glVertex3d ( corner, bottom  + (GLdouble) i * step, -corner);
    glVertex3d ( corner, bottom  + (GLdouble) i * step, corner);
    glVertex3d (-corner, bottom  + (GLdouble) i * step, corner); 

    glEnd();

  }  

  glDisable (GL_BLEND);

}

  
void drawArrayElement (const int elem) {

  GLdouble height;
  GLdouble refreshValue;

  height = (GLdouble) array.ary[elem];
  refreshValue = array.refresh[elem];

  // 4 sides  
  glBegin (GL_QUAD_STRIP);

  // 0
  glColor3d  (1.0 - refreshValue, 0.0, 0.2 * refreshValue);
  glVertex3d (-0.5, height, 0.5);

  // 1
  glColor3d  (1.0 - refreshValue, 0.0, refreshValue);
  glVertex3d (-0.5, 0.0, 0.5);

  // 2
  glColor3d  (1.0 - refreshValue, 0.0, 0.2 * refreshValue);
  glVertex3d (0.5, height, 0.5);

  // 3
  glColor3d  (1.0 - refreshValue, 0.0, refreshValue);
  glVertex3d (0.5, 0.0, 0.5);

  // 4
  glColor3d  (1.0 - refreshValue, 0.0, 0.2 * refreshValue);
  glVertex3d (0.5, height, -0.5);

  // 5
  glColor3d  (1.0 - refreshValue, 0.0, refreshValue);
  glVertex3d (0.5, 0.0, -0.5);

  // 6
  glColor3d  (1.0 - refreshValue, 0.0, 0.2 * refreshValue);
  glVertex3d (-0.5, height, -0.5);

  // 7
  glColor3d  (1.0 - refreshValue, 0.0, refreshValue);
  glVertex3d (-0.5, 0.0, -0.5);

  // 0
  glColor3d  (1.0 - refreshValue, 0.0, 0.2 * refreshValue);
  glVertex3d (-0.5, height, 0.5);

  // 1
  glColor3d  (1.0 - refreshValue, 0.0, refreshValue);
  glVertex3d (-0.5, 0.0, 0.5);

  glEnd();

  // top

  glBegin (GL_QUADS);

  glColor3d  (1.0 - refreshValue, 0.0, refreshValue);
  glVertex3d (-0.5, height,  0.5);
  glVertex3d ( 0.5, height,  0.5);
  glVertex3d ( 0.5, height, -0.5);
  glVertex3d (-0.5, height, -0.5);

  glEnd();

  // bottom

  glBegin (GL_QUADS);

  glColor3d  (1.0 - refreshValue, 0.0, 0.2 * refreshValue);
  glVertex3d (-0.5, 0.0,  0.5);
  glVertex3d (-0.5, 0.0, -0.5);
  glVertex3d ( 0.5, 0.0, -0.5);
  glVertex3d ( 0.5, 0.0,  0.5);

  glEnd();

}  

static void drawArray (const int size) {

  int i;

  glPushMatrix();
  glTranslated ((GLdouble) -size / 2.0 + 0.5, 0.0, 0.0);

  for (i = 0; i < size; i++) {

    drawArrayElement (i);
    glTranslatef (1.0, 0.0, 0.0);

  }

  glPopMatrix();

}

void drawScene (const int size) {
   
  drawAxes (size);
  drawArray (size);
  drawBox (size);
  drawDelayBar();
  drawTextScroller();
  drawTextFile();
  
}

  
