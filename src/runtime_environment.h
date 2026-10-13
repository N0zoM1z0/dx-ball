#ifndef DXBALL_RUNTIME_ENVIRONMENT_H
#define DXBALL_RUNTIME_ENVIRONMENT_H

#include "runtime_locale_backends.h"

#ifdef __cplusplus
extern "C" {
#endif

DXBALL_LOCALE_IMPORT unsigned short *DXBALL_LOCALE_OS_CALL GetEnvironmentStringsW(void);
DXBALL_LOCALE_IMPORT char *DXBALL_LOCALE_OS_CALL GetEnvironmentStrings(void);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL FreeEnvironmentStringsW(unsigned short *block);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL FreeEnvironmentStringsA(char *block);
char *dxball_crt_environment_strings(void);

#ifdef __cplusplus
}
#endif
#endif
