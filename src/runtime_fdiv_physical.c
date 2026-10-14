#include "runtime_fdiv_processors.h"

int _ms_p5_test_fdiv(void)
{
    /* Volatile operands keep this a real processor division test. Intermediate
       division/multiplication use x87 precision; only the residual is stored. */
    struct {
        volatile double dividend, divisor, residual;
    } probe;
    probe.divisor = 3145727.0;
    probe.dividend = 4195835.0;
    probe.residual = probe.dividend -
        (probe.dividend / probe.divisor) * probe.divisor;
    return !(probe.residual <= 1.0);
}
