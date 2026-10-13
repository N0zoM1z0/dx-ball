#include "runtime_float.h"

/* FUNCTION: DXBALL 0x0041E5C0 */
int __addl(unsigned int left, unsigned int right, unsigned int *result)
{
    int carry = 0;
    unsigned int sum = left + right;
    if (sum < left || sum < right) carry = 1;
    *result = sum;
    return carry;
}
