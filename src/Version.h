#ifndef __VERSION_H___
#define __VERSION_H___

/** the maximum length of the version string */
#define MAX_VERSION_LEN	32



/** get the version in the form <major>.<minor><subminor> as string */
char *getVersion (void);

/** get the date of the version as string */
char *getVersionDate (void);

#endif
