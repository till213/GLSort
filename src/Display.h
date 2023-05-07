#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <QOpenGLFunctions>

extern GLdouble curTheta;   /* position of the camera */
extern GLdouble curPhi;
extern GLdouble curDist;

void display (void);

#endif
