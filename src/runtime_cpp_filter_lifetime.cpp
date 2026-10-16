#include "runtime_cpp_filter_lifetime.h"

void dxball_cpp_install_unhandled_filter(void)
{
    dxball_crt_atexit(dxball_cpp_restore_unhandled_filter);
    dxball_cpp_previous_filter = SetUnhandledExceptionFilter(dxball_cpp_unhandled_filter);
}

void dxball_cpp_filter_initializer(void)
{
    dxball_cpp_install_unhandled_filter();
}

/* The complete original CRT$XCC record points at the initializer entry. */
#if defined(_MSC_VER)
#pragma data_seg(".CRT$XCC")
DxBallCrtCallback dxball_cpp_filter_initialization_entry = dxball_cpp_filter_initializer;
#pragma data_seg()
#else
DxBallCrtCallback dxball_cpp_filter_initialization_entry
    __attribute__((used, section(".CRT$XCC"))) = dxball_cpp_filter_initializer;
#endif
