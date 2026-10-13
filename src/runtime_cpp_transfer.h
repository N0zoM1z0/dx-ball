#ifndef DXBALL_RUNTIME_CPP_TRANSFER_H
#define DXBALL_RUNTIME_CPP_TRANSFER_H
#include "runtime_cpp_tables.h"

#if defined(_MSC_VER)
#define DXBALL_CPP_STDCALL __stdcall
#elif defined(__i386__)
#define DXBALL_CPP_STDCALL __attribute__((stdcall))
#else
#define DXBALL_CPP_STDCALL
#endif

/* The table consumers need only the first member. This owner consumes the
   complete header and three EH parameters; the remaining OS array is unused. */
typedef struct DxBallCppExceptionDetail {
    DxBallCppExceptionRecord record;
    unsigned int flags;
    DxBallCppExceptionRecord *chained_record;
    void *address;
    unsigned int parameter_count;
    size_t information[3];
} DxBallCppExceptionDetail;
struct DxBallCppRegistration {
    DxBallCppRegistration *previous;
    void (*frame_handler)(void);
    int state;
};
typedef int (*DxBallCppForwardHandler)(DxBallCppExceptionRecord *,
    DxBallCppRegistration *, DxBallCppContext *, void *,
    const DxBallCppFunctionPrefix *, int, DxBallCppRegistration *, int);
typedef struct DxBallCppThrowPrefix {
    unsigned int attributes;
    void (*destructor)(void);
    DxBallCppForwardHandler forward_handler;
} DxBallCppThrowPrefix;

#ifdef __cplusplus
extern "C" {
int dxball_cpp_rethrow_filter(DxBallCppExceptionPointers *);
int dxball_cpp_internal_frame_handler(DxBallCppExceptionRecord *,
    DxBallCppRegistration *, DxBallCppContext *, void *,
    const DxBallCppFunctionPrefix *, int, DxBallCppRegistration *, int);
void dxball_cpp_frame_unwind_to_state(DxBallCppRegistration *, void *,
    const DxBallCppFunctionPrefix *, int);
void dxball_cpp_find_handler(DxBallCppExceptionRecord *, DxBallCppRegistration *,
    DxBallCppContext *, void *, const DxBallCppFunctionPrefix *, unsigned char,
    int, DxBallCppRegistration *);
void dxball_cpp_build_catch_object(DxBallCppExceptionRecord *, DxBallCppRegistration *,
    const DxBallCppHandler *, const DxBallCppCatchableType *);
void DXBALL_CPP_STDCALL dxball_cpp_unwind_nested_frames(DxBallCppRegistration *,
    DxBallCppExceptionRecord *);
void *dxball_cpp_call_catch_block(DxBallCppExceptionRecord *, DxBallCppRegistration *,
    DxBallCppContext *, const DxBallCppFunctionPrefix *, void (*)(void), int, unsigned int);
void DXBALL_CPP_STDCALL dxball_cpp_jump_to_continuation(void *, DxBallCppRegistration *);
}
#endif
#endif
