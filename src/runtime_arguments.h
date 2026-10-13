#ifndef DXBALL_RUNTIME_ARGUMENTS_H
#define DXBALL_RUNTIME_ARGUMENTS_H

#include "runtime_fatal.h"
#include "runtime_multibyte.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "allocator.h"

extern int __argc;
extern char **__argv;
extern char *_pgmptr;
extern char **_environ;
extern char *_aenvptr;
extern char *_acmdln;

void dxball_crt_setargv(void);
void dxball_crt_setenvp(void);

#ifdef __cplusplus
}
#endif
#endif
