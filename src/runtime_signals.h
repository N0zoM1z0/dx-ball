#ifndef DXBALL_RUNTIME_SIGNALS_H
#define DXBALL_RUNTIME_SIGNALS_H

#include "runtime_fatal.h"

typedef struct _EXCEPTION_POINTERS DxBallCrtExceptionPointers;
typedef void (*DxBallCrtSignalHandler)(int signal_number);
typedef void (*DxBallCrtFloatingHandler)(int signal_number, int floating_code);
typedef union DxBallCrtSignalAction {
    size_t tag;
    DxBallCrtSignalHandler simple;
    DxBallCrtFloatingHandler floating;
} DxBallCrtSignalAction;
typedef struct DxBallCrtSignalRecord {
    DxBallCrtDword exception_code;
    int signal_number;
    DxBallCrtSignalAction action;
} DxBallCrtSignalRecord;

/* One complete initialized carrier:120 record bytes and20 metadata bytes on Win32. */
typedef struct DxBallCrtSignalState {
    DxBallCrtSignalRecord records[10];
    int first_floating;
    int floating_count;
    int record_count;
    int floating_code;
    DxBallCrtExceptionPointers *information;
} DxBallCrtSignalState;

/* Lookup scans the original carrier, including its terminal metadata reads. */
#if defined(__GNUC__)
#define DXBALL_CRT_SIGNAL_ALIAS __attribute__((may_alias))
#else
#define DXBALL_CRT_SIGNAL_ALIAS
#endif
#pragma pack(push, 1)
typedef struct DXBALL_CRT_SIGNAL_ALIAS DxBallCrtSignalProbe {
    DxBallCrtDword exception_code;
    int signal_number;
} DxBallCrtSignalProbe;
#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallCrtSignalState dxball_crt_signal_state;
DXBALL_CRT_IMPORT DxBallCrtLong DXBALL_CRT_OS_CALL UnhandledExceptionFilter(
    DxBallCrtExceptionPointers *information);
int dxball_crt_raise(int signal_number);
DxBallCrtSignalRecord *dxball_crt_siglookup(int signal_number);
DxBallCrtSignalRecord *dxball_crt_exception_lookup(DxBallCrtDword exception_code);
int dxball_crt_exception_filter(DxBallCrtDword exception_code,
                                DxBallCrtExceptionPointers *information);

#ifdef __cplusplus
}
#endif
#endif
