#ifndef __ARRAY_H_
#define __ARRAY_H_

#include <vector>
#include <GL/gl.h>


class Array {

 public:
  Array (const int size = 32);
  virtual ~Array (void) {};

  void setElem (const int val, const int pos);
  int getElem (const int pos);
  /** returns TRUE if elem at pos1 < elem at pos2 */
  bool isElemSmaller (const int pos1, const int pos2);
  void swapElems (const int pos1, const int pos2);
  int getSize (void);
  void resize (const int newSize);
  void reset (void);
  void copy (Array &src, Array &dst);
  void reverseOrder (void);
  void almostSorted (void);
  void randomOrder (void);

 private:
  friend void animateCB (void);				// needs access to refresh
  friend void drawArrayElement (const int elem);	// needs access to ary and refresh
  vector<int> ary;
  vector<GLfloat> refresh;

};

// global
extern Array array;

#endif
