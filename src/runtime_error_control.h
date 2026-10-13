#ifndef DXBALL_RUNTIME_ERROR_CONTROL_H
#define DXBALL_RUNTIME_ERROR_CONTROL_H

#include "runtime_fatal.h"

typedef int (DXBALL_CRT_OS_CALL *DxBallCrtProcedure)(void);
typedef int (DXBALL_CRT_OS_CALL *DxBallCrtMessageBox)(void *parent,
    const char *text, const char *caption, unsigned int flags);
typedef void *(DXBALL_CRT_OS_CALL *DxBallCrtActiveWindow)(void);
typedef void *(DXBALL_CRT_OS_CALL *DxBallCrtLastPopup)(void *window);

#ifdef __cplusplus
extern "C" {
#endif

DXBALL_CRT_IMPORT void *DXBALL_CRT_OS_CALL LoadLibraryA(const char *name);
DXBALL_CRT_IMPORT DxBallCrtProcedure DXBALL_CRT_OS_CALL GetProcAddress(
    void *module, const char *name);
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL IsBadReadPtr(const void *address, size_t bytes);
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL IsBadWritePtr(void *address, size_t bytes);
DXBALL_CRT_IMPORT int DXBALL_CRT_OS_CALL IsBadCodePtr(DxBallCrtProcedure address);
int dxball_crt_raise(int signal_number);
void dxball_crt_abort(void);

#ifdef __cplusplus
}

/* Original C++ runtime interfaces retain their unsigned32 count domain. */
int _ValidateRead(const void *address, unsigned int bytes);
int _ValidateWrite(void *address, unsigned int bytes);
int _ValidateExecute(DxBallCrtProcedure address);
#endif
#endif
