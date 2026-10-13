#ifndef DXBALL_RUNTIME_FDIV_PROCESSORS_H
#define DXBALL_RUNTIME_FDIV_PROCESSORS_H
#include "runtime_error_control.h"
#include "runtime_initialization.h"

/* Affinity APIs use pointer-width masks and real opaque OS handles. The
   original scan still visits precisely32 bit positions on every host. */
typedef void *(DXBALL_CRT_OS_CALL *DxBallFdivGetHandle)(void);
typedef int (DXBALL_CRT_OS_CALL *DxBallFdivGetAffinity)(void *, size_t *, size_t *);
typedef size_t (DXBALL_CRT_OS_CALL *DxBallFdivSetAffinity)(void *, size_t);
#ifdef __cplusplus
extern "C" {
#endif
/* Actual remaining physical x87 test, not an emulation callback. */
int _ms_p5_test_fdiv(void);
#ifdef __cplusplus
}
#endif
#endif
