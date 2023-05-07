#include <GL/glut.h>
#include <stdlib.h>
#include <dlfcn.h>	// for dlopen(), dlsym()
#include <stdio.h>	// for snprintf()
#include <sys/timeb.h>	// for ftime()


#include "Array.h"
#include "Camera.h"
#include "Delay.h"
#include "DelayBar.h"
#include "dirWalk.h"
#include "glutCallbacks.h"
#include "Registry.h"
#include "Resources.h"
#include "Sort.h"
#include "sortAlgorithms/SortAlgorithm.h"
#include "Text.h"
#include "TextScroller.h"
#include "Time.h"
#include "Translation.h"
#include "Utils.h"
#include "WinInfo.h"

// initial window size
#define WINWIDTH 	512
#define WINHEIGHT	512


void registerAlgorithms (const char *fileName) {

  void *handle;
  char pluginPath[255];
  SortAlgorithm *(*createInstance)(void);
  SortAlgorithm *instance;
  static int nRegistered = RM_ALGORITHMS;
  char *error;
  
  snprintf (pluginPath, 255, "%s/%s", pluginDir, fileName);

  handle = dlopen (pluginPath, RTLD_NOW);
  if (handle == NULL) {
    cerr << dlerror() << endl;
    cerr << "glSort: Could not open shared library: " << pluginPath << endl;
    return;
  }
  
  createInstance = (SortAlgorithm *(*)(void)) dlsym (handle, "createInstance");
  if ((error = dlerror()) != NULL) {
    cerr << error << endl;
    cerr << "glSort: Not a valid plugin: " << pluginPath << endl;
    return;
  }

  // create an instance and register it
  instance = (*createInstance)();
  Registry::addItem (nRegistered, instance);
  glutAddMenuEntry (instance->getName(), nRegistered);
  nRegistered++;

}  // registerAlgorithms()
  

static void init(void) {
  
  // initialize right button menu
  glutCreateMenu (rightMenuCB);
  glutAddMenuEntry (arySectionMsg, RM_NONE);
  glutAddMenuEntry (resetAryMsg, RM_RESETARRAY);
  glutAddMenuEntry (randomizeAryMsg, RM_RANDOMORDER);
  glutAddMenuEntry (reverseAryMsg, RM_REVERSEORDER);
  glutAddMenuEntry (almostAryMsg, RM_ALMOSTSORTED);
  glutAddMenuEntry ("Groesse verdoppeln", RM_DOUBLESIZE);
  glutAddMenuEntry ("Groesse halbieren", RM_HALFSIZE);
  glutAddMenuEntry (sortSectionMsg, RM_NONE);
  // initialize plugins and their menu entries
  dir::dirWalk (pluginDir, registerAlgorithms);
  // initialize the rest of menu entries
  glutAddMenuEntry (miscMsg, RM_NONE);
  glutAddMenuEntry (helpMsg, RM_HELP);
  glutAddMenuEntry (infoMsg, RM_INFO);
  glutAddMenuEntry (miscMsg, RM_NONE);
  glutAddMenuEntry (exitMsg, RM_EXIT);
  glutAttachMenu (GLUT_RIGHT_BUTTON);

  // update window info structure
  wininfo.width  = WINWIDTH;
  wininfo.height = WINHEIGHT;

  // reset camera position
  Camera::reset (0.0, 0.0, array.getSize() * 2.0, 0.0, 0.0);
 
  // GL settings
  glShadeModel (GL_SMOOTH);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  
  // enable depth test
  glEnable (GL_DEPTH_TEST);

  // enable backface culling
  glEnable (GL_CULL_FACE);
  glCullFace (GL_BACK);
  
  // start counting milliseconds
  ftime (&oldTime);

  initMyRand (131);

  // delay in milliseconds
  DelayDt = 100;

  // no sort thread is currently running
  isSortRunning = false;

  // initialize delay bar state
  initDelayBar();

  // initialize text scroller settings
  initTextScroller();

  // initialize help text
  initTextFile();

}



/** Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv) {

  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (WINWIDTH, WINHEIGHT);
  glutCreateWindow (argv[0]);
  glutSetWindowTitle (titleMsg);
  init();
  // glut callbacks (CB)
  glutReshapeFunc (reshapeCB);
  glutKeyboardFunc (keyboardCB);
  glutSpecialFunc(specialCB);
  glutDisplayFunc (displayCB);
  glutIdleFunc (animateCB);
  glutMouseFunc(mouseCB);
  glutMotionFunc(mouseMotionCB);

  // write welcome message
  writeScrollerLine (welcome1Msg);
  writeScrollerLine (welcome2Msg);
  writeScrollerLine (welcome3Msg);

  glutMainLoop();
  return 0;

}