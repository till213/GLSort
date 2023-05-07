#include <QtGlobal>

#include <QOpenGLFunctions>
#ifdef __MACH__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <math.h>

#include <Kernel/Array.h>
#include "Visual.h"
#include "Display.h"

#ifndef PI
#define PI 3.141592
#endif

#define INV_PI PI/180.0

GLdouble curTheta;   /* position of the camera */
GLdouble curPhi;
GLdouble curDist;

#include <Kernel/Array.h>

void display(void) {

    const std::size_t arraySize = array.getSize();

    GLdouble xEye,
        yEye,
        zEye;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* position the camera (the "eye") */
    glLoadIdentity();
    xEye = (GLdouble) (curDist * cos (INV_PI * (double) curTheta) * sin (INV_PI * (double) curPhi));
    yEye = (GLdouble) (curDist * sin (INV_PI * (double) curTheta)) + (GLdouble) arraySize / 2.0;
    zEye = (GLdouble) (curDist * cos (INV_PI * (double) curTheta) * cos (INV_PI * (double) curPhi));

    gluLookAt (xEye, yEye, zEye,
              0.0, (GLdouble) arraySize / 2.0, 0.0,
              0.0, 1.0, 0.0);

    drawScene (arraySize);

    //glutSwapBuffers();

}
