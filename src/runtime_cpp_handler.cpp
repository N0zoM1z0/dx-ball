#include "runtime_cpp_handler.h"
#include <string.h>

void dxball_cpp_find_handler(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, DxBallCppContext *context, void *dispatcher,
    const DxBallCppFunctionPrefix *function, unsigned char recursive, int nesting,
    DxBallCppRegistration *marker)
{
    int state = registration->state;
    if (state < -1 || state >= function->max_state)
        dxball_cpp_inconsistency();
    if (exception->code == 0xe06d7363U &&
            ((DxBallCppExceptionDetail *)exception)->parameter_count == 3 &&
            ((DxBallCppExceptionDetail *)exception)->information[0] == 0x19930520U &&
            ((DxBallCppExceptionDetail *)exception)->information[2] == 0) {
        if (!dxball_cpp_current_exception)
            return;
        exception = dxball_cpp_current_exception;
        context = dxball_cpp_current_context;
        if (!_ValidateRead(exception, 1))
            dxball_cpp_inconsistency();
        if (exception->code == 0xe06d7363U &&
                ((DxBallCppExceptionDetail *)exception)->parameter_count == 3 &&
                ((DxBallCppExceptionDetail *)exception)->information[0] == 0x19930520U &&
                ((DxBallCppExceptionDetail *)exception)->information[2] == 0)
            dxball_cpp_inconsistency();
    }
    if (exception->code == 0xe06d7363U &&
            ((DxBallCppExceptionDetail *)exception)->parameter_count == 3 &&
            ((DxBallCppExceptionDetail *)exception)->information[0] == 0x19930520U) {
        unsigned int high, low;
        const DxBallCppTryEntry *entry =
            dxball_cpp_select_try_range(function, nesting, state, &low, &high);
        while (low < high) {
            if (entry->try_low <= state && state <= entry->try_high) {
                const DxBallCppHandler *handler = entry->handlers;
                for (unsigned int handlers = entry->catch_count; handlers != 0; --handlers, ++handler) {
                    const DxBallCppThrowDetail *array_owner =
                        (const DxBallCppThrowDetail *)(const void *)
                        ((DxBallCppExceptionDetail *)exception)->information[2];
                    const DxBallCppCatchableArrayPrefix *array = array_owner->catchables;
                    const char *cursor = (const char *)array
                        + offsetof(DxBallCppCatchableArrayPrefix, first_type);
                    for (int types = array->count; types != 0; --types, cursor += sizeof(array->first_type)) {
                        const DxBallCppThrowDetail *throw_info =
                            (const DxBallCppThrowDetail *)(const void *)
                            ((DxBallCppExceptionDetail *)exception)->information[2];
                        const DxBallCppCatchableType *catchable =
                            *(const DxBallCppCatchableType *const *)(const void *)cursor;
                        int matches;
                        if (!handler->type || handler->type->name[0] == 0)
                            matches = 1;
                        else {
                            if ((handler->type != catchable->type &&
                                    strcmp(handler->type->name, catchable->type->name) != 0) ||
                                    ((catchable->properties & 2) && !(handler->adjectives & 8)) ||
                                    ((throw_info->prefix.attributes & 1) && !(handler->adjectives & 1)) ||
                                    ((throw_info->prefix.attributes & 2) && !(handler->adjectives & 2)))
                                matches = 0;
                            else
                                matches = 1;
                        }
                        if (matches) {
                            dxball_cpp_catch_it(exception, registration, context, dispatcher,
                                function, handler,
                                *(const DxBallCppCatchableType *const *)(const void *)cursor,
                                entry, nesting, marker);
                            goto next_try;
                        }
                    }
                }
            }
        next_try:
            ++entry;
            ++low;
        }
        if (recursive)
            dxball_cpp_destruct_exception_object(exception, 1);
    } else {
        if (!recursive) {
            dxball_cpp_find_foreign_handler(exception, registration, context, dispatcher,
                function, state, nesting, marker);
            return;
        }
        dxball_cpp_terminate();
    }
}
