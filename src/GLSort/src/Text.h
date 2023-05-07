#include <QOpenGLFunctions>

/** the maximum length of a filename (incl. terminating '\0') */
#define MAX_FILENAME_LEN	64
/** the maximum length of a line (incl. terminating '\0') */
#define MAX_LINE_LEN		64


// functions
// ---------

/** sets a (GLUT) text font */
void setTextFont (void *font);

/** returns the current (GLUT) text font */
void *getTextFont (void);

/** 
 * write a text (a 'string') onto the screen at coordinates (x, y) (lower left corner of the string)
 * with 'font' and 'alpha' blending
 */
void writeText (const char *string, const GLdouble x, const GLdouble y, const GLdouble alpha);

/** initialize text file writer */
void initTextFile(void);

/** draws a text file */
void drawTextFile (void);

/**
 * toggles the content of a text file given by 'filename'
 * on and off.
 */
void toggleTextFile (const char *filename);

/**
 * changes a currently showing text file. If to text file
 * is currently showing then this function has no effect.
 */
void changeTextFile (const char *fileName);

