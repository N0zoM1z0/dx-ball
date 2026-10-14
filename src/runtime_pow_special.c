#include "runtime_pow_special.h"
#include "runtime_fp_dispatch.h"
#include <math.h>
#include <string.h>

#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallPowWords {
#else
typedef struct DxBallPowWords {
#endif
    unsigned int low, high;
} DxBallPowWords;

int dxball_crt_pow_special(double base, double exponent, double *result)
{
    const DxBallPowWords *base_words = (const DxBallPowWords *)(const void *)&base;
    const DxBallPowWords *exponent_words = (const DxBallPowWords *)(const void *)&exponent;
    double magnitude = fabs(base);
    int status = 0, integer_type;
    if (exponent_words->high == 0x7ff00000U && exponent_words->low == 0) {
        /* The original x87 carry-bit branch accepts unordered here. */
        if (!(magnitude <= 1.0))
            *result = _d_inf.value;
        else if (magnitude < 1.0)
            *result = 0.0;
        else {
            *result = _d_ind.value;
            status = 1;
        }
    } else if (exponent_words->high == 0xfff00000U && exponent_words->low == 0) {
        if (!(magnitude <= 1.0))
            *result = 0.0;
        else if (magnitude < 1.0)
            *result = _d_inf.value;
        else {
            *result = _d_ind.value;
            status = 1;
        }
    } else if (base_words->high == 0x7ff00000U && base_words->low == 0) {
        if (!(exponent <= 0.0))
            *result = _d_inf.value;
        else if (exponent < 0.0)
            *result = 0.0;
        else
            *result = 1.0;
    } else if (base_words->high == 0xfff00000U && base_words->low == 0) {
        double selected;
        integer_type = dxball_crt_double_integer_type(exponent);
        if (!(exponent <= 0.0)) {
            selected = integer_type == 1 ? -_d_inf.value : _d_inf.value;
            memcpy((unsigned char *)result + 4,
                   (const unsigned char *)&selected + 4, 4);
            memcpy(result, &selected, 4);
        } else if (exponent < 0.0) {
            selected = integer_type == 1 ? _d_mzero.value : 0.0;
            memcpy((unsigned char *)result + 4,
                   (const unsigned char *)&selected + 4, 4);
            memcpy(result, &selected, 4);
        } else
            *result = 1.0;
    }
    return status;
}
