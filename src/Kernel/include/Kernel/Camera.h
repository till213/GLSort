#include <QOpenGLFunctions>

namespace Camera {
  
  struct Camera {
  
    // position of the camera
    GLdouble phi;   
    GLdouble theta;
    GLdouble dist;
    
    // motion of the camera
    GLdouble thetaInc;
    GLdouble phiInc;
    
  };
  
  /** global instance of camera */
  extern struct Camera instance;
  
  void reset (GLdouble phi,
	      GLdouble theta,
	      GLdouble dist,
	      GLdouble phiInc,
	      GLdouble thetaInc);
  
};
