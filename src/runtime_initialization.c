#include "runtime_initialization.h"
#include "runtime_float_format.h"

void dxball_crt_initialize_conversion_table(void)
{
    _cfltcvt_tab.crop.active = dxball_crt_crop_float_zeros;
    _cfltcvt_tab.assign.active = dxball_crt_assign_float;
    _cfltcvt_tab.force_decimal.active = dxball_crt_force_decimal_point;
    _cfltcvt_tab.positive.active = dxball_crt_float_positive;
    _cfltcvt_tab.convert.active = dxball_crt_format_float;
    _cfltcvt_tab.convert_compat.active = dxball_crt_format_float;
}

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
