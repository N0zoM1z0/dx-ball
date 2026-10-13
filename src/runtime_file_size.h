#ifndef DXBALL_RUNTIME_FILE_SIZE_H
#define DXBALL_RUNTIME_FILE_SIZE_H

#include "runtime_stream_transfer.h"

#ifdef __cplusplus
extern "C" {
#endif
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL SetEndOfFile(void *handle);
int dxball_crt_chsize(int descriptor, DxBallCrtLong size);
int dxball_crt_fcloseall(void);
#ifdef __cplusplus
}
#endif
#endif
