#ifndef DXBALL_RUNTIME_CPP_OBJECT_H
#define DXBALL_RUNTIME_CPP_OBJECT_H

#include "runtime_cpp_handler.h"

/* Complete catchable metadata consumed by object construction. */
typedef struct DxBallCppCatchableDetail {
    DxBallCppCatchableType prefix;
    DxBallCppPmd displacement;
    int size;
    void (*copy)(void);
} DxBallCppCatchableDetail;

/* The original stdcall-to-thiscall trampolines take opaque code addresses. */
void DXBALL_CPP_STDCALL _CallMemberFunction0(void *, void *);
void DXBALL_CPP_STDCALL _CallMemberFunction1(void *, void *, void *);
void DXBALL_CPP_STDCALL _CallMemberFunction2(void *, void *, void *, int);

#endif
