#include <GL/gl.h>

#include "Camera.h"

// global
// ------

namespace Camera {
  struct Camera instance;
};

// public
// ------

void Camera::reset (GLdouble phi,
		    GLdouble theta,
		    GLdouble dist,
		    GLdouble phiInc,
		    GLdouble thetaInc) {
  
  instance.phi      = phi;
  instance.theta    = theta;
  instance.dist     = dist;
  
  instance.phiInc   = phiInc;
  instance.thetaInc = thetaInc;
  
}  // resetCamera()
		  
