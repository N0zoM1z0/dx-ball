#include "runtime_arguments.h"

/* stdargv.obj and stdenvp.obj consume these as external definitions. */
int __argc = 0;
char **__argv = 0;
char *_pgmptr = 0;
char **_environ = 0;
char *_aenvptr = 0;
