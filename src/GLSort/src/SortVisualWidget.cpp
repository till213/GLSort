/**
 * GLSort - Sort algorithm visualisation
 *
 * Copyright (c) Oliver Knoll
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <float.h>	// for DBL_MAX

#include <QOpenGLFunctions>
#include <GL/glu.h>

#include <Kernel/Array.h>
#include <Kernel/Camera.h>
#include "Visual.h"
#include "WinInfo.h"
#include "SortVisualWidget.h"

#ifndef PI
#define PI 3.141592
#endif

#define INV_PI PI / 180.0

// PUBLIC

SortVisualWidget::SortVisualWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

// PROTECTED

void SortVisualWidget::initializeGL() noexcept
{
    initializeOpenGLFunctions();

    // update window info structure
    wininfo.width  = this->width();
    wininfo.height = this->height();

    // reset camera position
    Camera::reset (0.0, 0.0, array.getSize() * 2.0, 0.0, 0.0);

    // GL settings
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.3, 0.3, 0.33, 0.0);

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // enable backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void SortVisualWidget::paintGL() noexcept
{
    GLdouble xEye,
        yEye,
        zEye;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* position the camera (the "eye") */
    glLoadIdentity();
    xEye = (GLdouble) (Camera::instance.dist * cos (INV_PI * (double) Camera::instance.theta) * sin (INV_PI * (double) Camera::instance.phi));
    yEye = (GLdouble) (Camera::instance.dist * sin (INV_PI * (double) Camera::instance.theta)) + (GLdouble) array.getSize() / 2.0;
    zEye = (GLdouble) (Camera::instance.dist * cos (INV_PI * (double) Camera::instance.theta) * cos (INV_PI * (double) Camera::instance.phi));

    gluLookAt (xEye, yEye, zEye,
              0.0, (GLdouble) array.getSize() / 2.0, 0.0,
              0.0, 1.0, 0.0);

    drawScene(array.getSize());
}

void SortVisualWidget::resizeGL(int width, int height) noexcept
{
    wininfo.width  = width;
    wininfo.height = height;

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)width / (GLdouble)height, 1.0, (GLdouble) DBL_MAX);
    glMatrixMode (GL_MODELVIEW);
}
