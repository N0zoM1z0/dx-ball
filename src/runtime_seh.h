#ifndef DXBALL_RUNTIME_SEH_H
#define DXBALL_RUNTIME_SEH_H

#include "state_types.h"

/* The unwind handler consumes only the first two EXCEPTION_RECORD words. */
typedef struct DxBallSehExceptionPrefix {
    DxBallUInt code;
    DxBallUInt flags;
} DxBallSehExceptionPrefix;

typedef enum DxBallSehDisposition {
    DXBALL_SEH_CONTINUE_EXECUTION = 0,
    DXBALL_SEH_CONTINUE_SEARCH = 1,
    DXBALL_SEH_NESTED_EXCEPTION = 2,
    DXBALL_SEH_COLLIDED_UNWIND = 3
} DxBallSehDisposition;

#ifdef __cplusplus
extern "C" {
#endif

DxBallSehDisposition dxball_crt_unwind_handler(DxBallSehExceptionPrefix *exception,
    void *frame, void *context, void **dispatcher);

#ifdef __cplusplus
}
#endif
#endif
