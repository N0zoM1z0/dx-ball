#ifndef DXBALL_FILE_H
#define DXBALL_FILE_H

#include "platform.h"

/* Shared Kernel32 services used by file loading and MDS mapping. */
extern DxBallHandle (DXBALL_DDCALL *dxball_file_create)(const char *, DxBallUInt,
    DxBallUInt, void *, DxBallUInt, DxBallUInt, DxBallHandle);
extern DxBallUInt (DXBALL_DDCALL *dxball_file_size)(DxBallHandle, DxBallUInt *);
extern DxBallInt (DXBALL_DDCALL *dxball_file_read)(DxBallHandle, void *,
    DxBallUInt, DxBallUInt *, void *);
extern DxBallInt (DXBALL_DDCALL *dxball_file_close)(DxBallHandle);
extern const char dxball_file_fallback_prefix[];

void *dxball_load_binary_file(const char *path, void *destination, DxBallInt allocate);

#endif
