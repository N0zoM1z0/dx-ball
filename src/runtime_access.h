#ifndef DXBALL_RUNTIME_ACCESS_H
#define DXBALL_RUNTIME_ACCESS_H
#include "runtime_lowio.h"

#ifdef __cplusplus
extern "C" {
#endif
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL GetFileAttributesA(const char *path);
int dxball_crt_access(const char *path, int mode);
#ifdef __cplusplus
}
#endif
#endif
