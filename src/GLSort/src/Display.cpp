#include <QOpenGLFunctions>
#include <OpenGL/glu.h>
#include <math.h>

#include "Array.h"
#include "Visual.h"
#include "Display.h"

#ifndef PI
#define PI 3.141592
#endif

#define INV_PI PI/180.0

GLdouble curTheta;   /* position of the camera */
GLdouble curPhi;
GLdouble curDist;

void display(void) {

  GLdouble xEye,
    yEye,
    zEye;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* position the camera (the "eye") */
  glLoadIdentity();
  xEye = (GLdouble) (curDist * cos (INV_PI * (double) curTheta) * sin (INV_PI * (double) curPhi));
  yEye = (GLdouble) (curDist * sin (INV_PI * (double) curTheta)) + (GLdouble) ARRAYSIZE / 2.0;
  zEye = (GLdouble) (curDist * cos (INV_PI * (double) curTheta) * cos (INV_PI * (double) curPhi));

  gluLookAt (xEye, yEye, zEye,
	     0.0, (GLdouble) ARRAYSIZE / 2.0, 0.0,
	     0.0, 1.0, 0.0); 
   
  drawScene (ARRAYSIZE);

  //glutSwapBuffers();

}
