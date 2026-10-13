#ifndef DXBALL_RUNTIME_LOWIO_STARTUP_H
#define DXBALL_RUNTIME_LOWIO_STARTUP_H

#include "runtime_fatal.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "allocator.h"

/* STARTUPINFOA:68 bytes in the original ABI; host pointers grow naturally. */
typedef struct DxBallCrtStartupInfo {
    DxBallCrtDword size;
    char *reserved;
    char *desktop;
    char *title;
    DxBallCrtDword x;
    DxBallCrtDword y;
    DxBallCrtDword width;
    DxBallCrtDword height;
    DxBallCrtDword columns;
    DxBallCrtDword rows;
    DxBallCrtDword fill;
    DxBallCrtDword flags;
    unsigned short show;
    unsigned short reserved_count;
    unsigned char *reserved_data;
    void *input;
    void *output;
    void *error;
} DxBallCrtStartupInfo;

/* The inherited packet is byte-packed: its handle array follows count flags. */
#if defined(__GNUC__)
#define DXBALL_CRT_PACKET_ALIAS __attribute__((may_alias))
#else
#define DXBALL_CRT_PACKET_ALIAS
#endif
#pragma pack(push, 1)
typedef struct DXBALL_CRT_PACKET_ALIAS DxBallCrtInheritedCount {
    int value;
} DxBallCrtInheritedCount;
typedef struct DXBALL_CRT_PACKET_ALIAS DxBallCrtInheritedHandle {
    DxBallCrtOsHandle value;
} DxBallCrtInheritedHandle;
#pragma pack(pop)

DXBALL_CRT_IMPORT void DXBALL_CRT_OS_CALL GetStartupInfoA(DxBallCrtStartupInfo *startup);
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL GetFileType(void *handle);
DXBALL_CRT_IMPORT unsigned int DXBALL_CRT_OS_CALL SetHandleCount(unsigned int count);
void dxball_crt_initialize_lowio(void);

#ifdef __cplusplus
}
#endif
#endif
