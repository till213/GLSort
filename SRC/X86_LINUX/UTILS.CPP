#include <stdlib.h>	// for rand(), srand()

#include "Utils.h"



/**
 * returns the minimum and its position in the array 'ary' - the search takes
 * place in the range lo <= x < hi, i.e. when the array has length n and the
 * search should go over the whole array, then lo = 0 and hi = n
*/
void searchMin (const int ary[], const int lo, const int hi, int *pos, int *ncomp) {

  int i;
  int curMin;

  curMin = ary[lo];
  *pos = lo;

  for (i = lo + 1; i < hi; i++) {

    (*ncomp)++;
    if (ary[i] < curMin) {

      // store the current position
      *pos = i;

      // update the current minimum
      curMin = ary[i];

    }
	
  }  /* for (i) */

}



void initMyRand (const unsigned int seed) {

  srand (seed);

}

int myRand (const int n) {

  return ((int) ((double) n * (double) rand() / ((double) RAND_MAX + 1.0) + 0.5));

} 
	
    
    
