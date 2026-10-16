#include "runtime_cpp_object.h"
#include <string.h>

/* FUNCTION: DXBALL 0x0041B960 */
void dxball_cpp_build_catch_object(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, const DxBallCppHandler *handler,
    const DxBallCppCatchableType *catchable)
{
    const DxBallCppCatchableDetail *detail = (const DxBallCppCatchableDetail *)catchable;
    if (handler->type && handler->type->name[0] && handler->catch_displacement) {
        void *destination = (char *)registration + sizeof(*registration)
            + handler->catch_displacement;
        __try {
            if (handler->adjectives & 8) {
                if (_ValidateRead((void *)((DxBallCppExceptionDetail *)exception)->information[1], 1)
                        && _ValidateWrite(destination, 1)) {
                    *(void **)destination = (void *)((DxBallCppExceptionDetail *)exception)->information[1];
                    *(void **)destination = dxball_cpp_adjust_pointer(*(void **)destination,
                        detail->displacement);
                } else dxball_cpp_inconsistency();
            } else if (catchable->properties & 1) {
                if (_ValidateRead((void *)((DxBallCppExceptionDetail *)exception)->information[1], 1)
                        && _ValidateWrite(destination, 1)) {
                    memmove(destination, (void *)((DxBallCppExceptionDetail *)exception)->information[1],
                        detail->size);
                    if (detail->size == (int)sizeof(void *) && *(void **)destination)
                        *(void **)destination = dxball_cpp_adjust_pointer(*(void **)destination,
                            detail->displacement);
                } else dxball_cpp_inconsistency();
            } else if (!detail->copy) {
                if (_ValidateRead((void *)((DxBallCppExceptionDetail *)exception)->information[1], 1)
                        && _ValidateWrite(destination, 1)) {
                    memmove(destination,
                        dxball_cpp_adjust_pointer((void *)((DxBallCppExceptionDetail *)exception)->information[1],
                            detail->displacement), detail->size);
                } else dxball_cpp_inconsistency();
            } else {
                if (_ValidateRead((void *)((DxBallCppExceptionDetail *)exception)->information[1], 1)
                        && _ValidateWrite(destination, 1)
                        && _ValidateExecute((DxBallCrtProcedure)detail->copy)) {
                    if (catchable->properties & 4)
                        _CallMemberFunction2(destination, (void *)detail->copy,
                            dxball_cpp_adjust_pointer((void *)((DxBallCppExceptionDetail *)exception)->information[1],
                                detail->displacement), 1);
                    else
                        _CallMemberFunction1(destination, (void *)detail->copy,
                            dxball_cpp_adjust_pointer((void *)((DxBallCppExceptionDetail *)exception)->information[1],
                                detail->displacement));
                } else dxball_cpp_inconsistency();
            }
        } __except (1) {
            dxball_cpp_terminate();
        }
    }
}

/* FUNCTION: DXBALL 0x0041BB60 */
void dxball_cpp_destruct_exception_object(DxBallCppExceptionRecord *exception,
    unsigned char throw_not_allowed)
{
    if (exception && ((const DxBallCppThrowPrefix *)
            ((DxBallCppExceptionDetail *)exception)->information[2])->destructor) {
        __try {
            _CallMemberFunction0(
                (void *)((DxBallCppExceptionDetail *)exception)->information[1],
                (void *)((const DxBallCppThrowPrefix *)
                    ((DxBallCppExceptionDetail *)exception)->information[2])->destructor);
        } __except (throw_not_allowed ? 1 : 0) {
            dxball_cpp_terminate();
        }
    }
}
