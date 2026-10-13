#include "runtime_initialization.h"

void dxball_crt_initialize_runtime(void)
{
    if (_FPinit)
        _FPinit();
    dxball_crt_run_initializers(__xi_a, __xi_z);
    dxball_crt_run_initializers(__xc_a, __xc_z);
}

void dxball_crt_initialize_math(void)
{
    dxball_crt_initialize_conversion_table();
    _adjust_fdiv = dxball_crt_test_fdiv_processors();
    dxball_crt_set_default_precision();
    _clrfp();
}

void dxball_crt_fp_thread_noop(void)
{
}

void dxball_crt_set_default_precision(void)
{
    _controlfp(0x10000, 0x30000);
}
