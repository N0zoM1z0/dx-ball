#ifndef DXBALL_RUNTIME_LOWIO_H
#define DXBALL_RUNTIME_LOWIO_H

#include "runtime_file_modes.h"
#include "state_types.h"

#if defined(_WIN32)
#define DXBALL_CRT_IMPORT __declspec(dllimport)
#define DXBALL_CRT_OS_CALL __stdcall
typedef unsigned long DxBallCrtDword;
typedef long DxBallCrtLong;
#else
#define DXBALL_CRT_IMPORT
#define DXBALL_CRT_OS_CALL
typedef DxBallUInt DxBallCrtDword;
typedef DxBallInt DxBallCrtLong;
#endif

/* VC4 io.h exposes a signed long handle. Native handles keep pointer width. */
#if defined(_WIN32) && !defined(_WIN64)
typedef long DxBallCrtOsHandle;
#else
typedef ptrdiff_t DxBallCrtOsHandle;
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallCrtDword _doserrno;

DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL WriteFile(void *handle, const void *buffer,
    DxBallCrtDword bytes, DxBallCrtDword *written, void *overlapped);
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL FlushFileBuffers(void *handle);
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL GetLastError(void);
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL SetFilePointer(void *handle,
    DxBallCrtLong offset, DxBallCrtLong *high_offset, DxBallCrtDword origin);

DxBallCrtOsHandle dxball_crt_get_osfhandle(int descriptor);
int dxball_crt_write(int descriptor, const void *buffer, unsigned int bytes);
int dxball_crt_commit(int descriptor);
DxBallCrtLong dxball_crt_seek(int descriptor, DxBallCrtLong offset, int origin);
void dxball_crt_map_os_error(DxBallCrtDword error);

#ifdef __cplusplus
}
#endif
#endif
