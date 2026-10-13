#include "runtime_cpp_filter.h"

/* Genuine unhandld.obj zero-initialized saved-filter storage. */
DxBallCppUnhandledFilter dxball_cpp_previous_filter;

DxBallCrtLong DXBALL_CRT_OS_CALL dxball_cpp_unhandled_filter(DxBallCppExceptionPointers *information)
{
    const DxBallCppExceptionDetail *record = (const DxBallCppExceptionDetail *)information->record;
    if (record->record.code == 0xe06d7363U && record->parameter_count == 3 &&
            record->information[0] == 0x19930520U) {
        dxball_cpp_terminate();
        return 1;
    }
    if (dxball_cpp_previous_filter && _ValidateExecute(
            (DxBallCrtProcedure)(void (*)(void))dxball_cpp_previous_filter))
        return dxball_cpp_previous_filter(information);
    return 0;
}

void dxball_cpp_restore_unhandled_filter(void)
{
    SetUnhandledExceptionFilter(dxball_cpp_previous_filter);
}
