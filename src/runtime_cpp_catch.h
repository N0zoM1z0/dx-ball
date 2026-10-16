#ifndef DXBALL_RUNTIME_CPP_CATCH_H
#define DXBALL_RUNTIME_CPP_CATCH_H

#include "runtime_cpp_handler.h"

/* The compiler's saved stack slot immediately precedes its registration. */
typedef struct DxBallCppFrameStackPrefix {
    void *saved_stack;
    DxBallCppRegistration registration;
} DxBallCppFrameStackPrefix;

/* Opaque original CRT tags preserve the real C++ transport symbol and ABI. */
struct EHRegistrationNode;
struct _s_FuncInfo;
void *_CallCatchBlock2(EHRegistrationNode *, const _s_FuncInfo *,
    void *, int, unsigned long);

#endif
