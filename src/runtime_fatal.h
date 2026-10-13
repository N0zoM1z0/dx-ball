#ifndef DXBALL_RUNTIME_FATAL_H
#define DXBALL_RUNTIME_FATAL_H

#include "runtime_lowio_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "termination.h"

typedef void (*DxBallCrtExitRoutine)(unsigned int status);
extern int dxball_crt_error_mode;
extern DxBallCrtExitRoutine dxball_crt_exit_routine;
extern DxBallCrtCallback dxball_crt_debug_message;

DXBALL_CRT_IMPORT void *DXBALL_CRT_OS_CALL GetStdHandle(DxBallCrtDword standard);
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL GetModuleFileNameA(
    void *module, char *buffer, DxBallCrtDword capacity);
int __crtMessageBoxA(const char *text, const char *caption, unsigned int flags);

/* Error reasons are the original seventeen catalog entries. */
void dxball_crt_write_error(int reason);
void dxball_crt_error_banner(void);
void dxball_crt_amsg_exit(int reason);

#ifdef __cplusplus
}
#endif
#endif
