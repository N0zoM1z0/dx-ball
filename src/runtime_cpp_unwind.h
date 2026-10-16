#ifndef DXBALL_RUNTIME_CPP_UNWIND_H
#define DXBALL_RUNTIME_CPP_UNWIND_H

#include "runtime_cpp_transfer.h"

typedef struct DxBallCppUnwindEntry {
    int to_state;
    void (*action)(void);
} DxBallCppUnwindEntry;

/* Original frame-setting transport; this owner supplies no substitute body. */
extern "C" void *DXBALL_CPP_STDCALL _CallSettingFrame(
    void *, DxBallCppRegistration *, unsigned long);

#endif
