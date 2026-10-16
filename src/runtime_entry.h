#ifndef DXBALL_RUNTIME_ENTRY_H
#define DXBALL_RUNTIME_ENTRY_H

#include "runtime_arguments.h"
#include "runtime_environment.h"
#include "runtime_initialization.h"
#include "runtime_lowio_startup.h"
#include "runtime_codepage.h"
#include "runtime_signals.h"
#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int _osver, _winver, _winmajor, _winminor;
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL GetVersion(void);
DXBALL_CRT_IMPORT char *DXBALL_CRT_OS_CALL GetCommandLineA(void);
DXBALL_CRT_IMPORT void *DXBALL_CRT_OS_CALL GetModuleHandleA(const char *name);
void dxball_crt_startup(void);

#ifdef __cplusplus
}
#endif
#endif
