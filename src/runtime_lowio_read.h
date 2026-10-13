#ifndef DXBALL_RUNTIME_LOWIO_READ_H
#define DXBALL_RUNTIME_LOWIO_READ_H

#include "runtime_lowio.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int dxball_crt_application_type;

DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL ReadFile(void *handle, void *buffer,
    DxBallCrtDword bytes, DxBallCrtDword *read, void *overlapped);
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL CloseHandle(void *handle);
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL SetStdHandle(DxBallCrtDword standard, void *handle);

int dxball_crt_read(int descriptor, void *buffer, unsigned int bytes);
int dxball_crt_close(int descriptor);
int dxball_crt_free_osfhandle(int descriptor);
int dxball_crt_set_osfhandle(int descriptor, DxBallCrtOsHandle handle);

#ifdef __cplusplus
}
#endif
#endif
