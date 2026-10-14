#include "runtime_cpp_transfer.h"

int dxball_cpp_rethrow_filter(DxBallCppExceptionPointers *pointers)
{
    const DxBallCppExceptionDetail *record = (const DxBallCppExceptionDetail *)pointers->record;
    if (record->record.code == 0xe06d7363U && record->parameter_count == 3 &&
            record->information[0] == 0x19930520U && record->information[2] == 0)
        return 1;
    return 0;
}

int dxball_cpp_internal_frame_handler(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, DxBallCppContext *context, void *dispatcher,
    const DxBallCppFunctionPrefix *function, int nesting, DxBallCppRegistration *marker,
    int recursive)
{
    const DxBallCppExceptionDetail *details = (const DxBallCppExceptionDetail *)exception;
    if (function->magic != 0x19930520U)
        dxball_cpp_inconsistency();
    if (details->flags & 0x66) {
        if (function->max_state != 0 && nesting == 0)
            dxball_cpp_frame_unwind_to_state(registration, dispatcher, function, -1);
        return 1;
    }
    if (function->try_count != 0) {
        if (exception->code == 0xe06d7363U && details->information[0] > 0x19930520U) {
            const DxBallCppThrowPrefix *throw_info =
                (const DxBallCppThrowPrefix *)(const void *)details->information[2];
            if (throw_info->forward_handler)
                return throw_info->forward_handler(exception, registration, context,
                    dispatcher, function, nesting, marker, recursive);
        }
        dxball_cpp_find_handler(exception, registration, context, dispatcher, function,
            (unsigned char)recursive, nesting, marker);
    }
    return 1;
}

void dxball_cpp_catch_it(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, DxBallCppContext *context, void *dispatcher,
    const DxBallCppFunctionPrefix *function, const DxBallCppHandler *handler,
    const DxBallCppCatchableType *catchable, const DxBallCppTryEntry *entry, int nesting,
    DxBallCppRegistration *marker)
{
    if (catchable)
        dxball_cpp_build_catch_object(exception, registration, handler, catchable);
    if (!marker)
        dxball_cpp_unwind_nested_frames(registration, exception);
    else
        dxball_cpp_unwind_nested_frames(marker, exception);
    dxball_cpp_frame_unwind_to_state(registration, dispatcher, function, entry->try_low);
    registration->state = entry->try_high + 1;
    void *continuation = dxball_cpp_call_catch_block(exception, registration, context,
        function, handler->handler, nesting, 0x100);
    if (continuation)
        dxball_cpp_jump_to_continuation(continuation, registration);
}
