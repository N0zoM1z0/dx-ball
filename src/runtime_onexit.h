#ifndef DXBALL_RUNTIME_ONEXIT_H
#define DXBALL_RUNTIME_ONEXIT_H

#include "termination.h"
#include "runtime_resize.h"

/* VC4 _onexit_t returns int; the existing termination slots discard results. */
typedef int (DXBALL_NEW_CALL *DxBallOnExitCallback)(void);

#ifdef __cplusplus
extern "C" {
#endif
DxBallOnExitCallback DXBALL_NEW_CALL dxball_crt_onexit(DxBallOnExitCallback callback);
int DXBALL_NEW_CALL dxball_crt_atexit(DxBallCrtCallback callback);
#ifdef __cplusplus
}
#endif
#endif
