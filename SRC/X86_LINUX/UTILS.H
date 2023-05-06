#ifndef __UTILS_H_
#define __UTILS_H_

#ifndef bool
#define bool char
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif



/**
 * returns the position of the minimum in the array 'ary' - the search takes
 * place in the range lo <= x < hi, i.e. when the array has length n and the
 * search should go over the whole array, then lo = 0 and hi = n
*/
void searchMin (const int ary[], const int lo, const int hi, int *pos, int *ncomp);



void initMyRand (const unsigned int seed);

int myRand (const int n);

#endif
