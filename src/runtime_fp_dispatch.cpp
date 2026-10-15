#include "runtime_fp_dispatch.h"

#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallDispatchDoubleBits {
#else
typedef struct DxBallDispatchDoubleBits {
#endif
    unsigned int low, high;
} DxBallDispatchDoubleBits;
typedef union DxBallDispatchDoubleWork {
    double value;
    DxBallDispatchDoubleBits bits;
    unsigned short words[4];
    unsigned char bytes[8];
} DxBallDispatchDoubleWork;

void dxball_crt_raise_float_exception(DxBallIeeeRecord *record, unsigned int *control,
                                     unsigned int flags, int operation,
                                     const double *argument, double *result)
{
    unsigned int code, status;
    DxBallDispatchDoubleBits *operand_bits, *result_bits;
    const DxBallDispatchDoubleBits *input_bits, *returned_bits;
    /* The caller reaches this boundary only with a nonzero unhandled IEEE
       cause among bits0..4. No exception code exists for an empty cause. */
    record->cause.raw = 0;
    record->enable.raw = 0;
    record->status.raw = 0;
    if (flags & 0x10) { code = 0xc000008fU; record->cause.bits.inexact = 1; }
    if (flags & 0x02) { code = 0xc0000093U; record->cause.bits.underflow = 1; }
    if (flags & 0x01) { code = 0xc0000091U; record->cause.bits.overflow = 1; }
    if (flags & 0x04) { code = 0xc000008eU; record->cause.bits.zero_divide = 1; }
    if (flags & 0x08) { code = 0xc0000090U; record->cause.bits.invalid = 1; }
    record->enable.bits.invalid = (*control & 0x01) == 0;
    record->enable.bits.zero_divide = (*control & 0x04) == 0;
    record->enable.bits.overflow = (*control & 0x08) == 0;
    record->enable.bits.underflow = (*control & 0x10) == 0;
    record->enable.bits.inexact = (*control & 0x20) == 0;
    status = (unsigned int)_statfp();
    if (status & 0x01) record->status.bits.invalid = 1;
    if (status & 0x04) record->status.bits.zero_divide = 1;
    if (status & 0x08) record->status.bits.overflow = 1;
    if (status & 0x10) record->status.bits.underflow = 1;
    if (status & 0x20) record->status.bits.inexact = 1;
    switch (*control & 0xc00) {
    case 0: record->rounding = 0; break;
    case 0x400: record->rounding = 1; break;
    case 0x800: record->rounding = 2; break;
    case 0xc00: record->rounding = 3; break;
    }
    switch (*control & 0x300) {
    case 0: record->precision = 2; break;
    case 0x200: record->precision = 1; break;
    case 0x300: record->precision = 0; break;
    }
    record->operation = (unsigned int)operation;
    record->operand1.valid = 1;
    record->operand1.format = 1;
    operand_bits = (DxBallDispatchDoubleBits *)(void *)&record->operand1.value.fp64;
    input_bits = (const DxBallDispatchDoubleBits *)(const void *)argument;
    operand_bits->high = input_bits->high;
    operand_bits->low = input_bits->low;
    record->result.valid = 1;
    record->result.format = 1;
    result_bits = (DxBallDispatchDoubleBits *)(void *)&record->result.value.fp64;
    returned_bits = (const DxBallDispatchDoubleBits *)(const void *)result;
    result_bits->high = returned_bits->high;
    result_bits->low = returned_bits->low;
    _clrfp();
    RaiseException(code, 0, 1, (const size_t *)(const void *)&record);
    if (record->enable.bits.invalid) *control &= 0xfffffffeU;
    if (record->enable.bits.zero_divide) *control &= 0xfffffffbU;
    if (record->enable.bits.overflow) *control &= 0xfffffff7U;
    if (record->enable.bits.underflow) *control &= 0xffffffefU;
    if (record->enable.bits.inexact) *control &= 0xffffffdfU;
    switch (record->rounding) {
    case 0: *control &= 0xfffff3ffU; break;
    case 1: *control = (*control & 0xfffff7ffU) | 0x400; break;
    case 2: *control = (*control & 0xfffffbffU) | 0x800; break;
    case 3: *control |= 0xc00; break;
    }
    /* Preserve the shipped precision writeback's rounding-bit clear mask. */
    switch (record->precision) {
    case 0: *control = (*control & 0xfffff3ffU) | 0x300; break;
    case 1: *control = (*control & 0xfffff3ffU) | 0x200; break;
    case 2: *control &= 0xfffff3ffU; break;
    }
    returned_bits = (const DxBallDispatchDoubleBits *)(const void *)&record->result.value.fp64;
    result_bits = (DxBallDispatchDoubleBits *)(void *)result;
    result_bits->high = returned_bits->high;
    result_bits->low = returned_bits->low;
}

int dxball_crt_handle_float_exception(unsigned int flags, double *result, unsigned int control)
{
    unsigned int pending = flags & 0x1f;
    DxBallDispatchDoubleBits *result_bits = (DxBallDispatchDoubleBits *)(void *)result;
    DxBallDispatchDoubleWork fraction;
    int exponent, adjusted_exponent, inexact, negative;
    if ((flags & 0x08) && (control & 0x01)) {
        pending &= ~0x08U;
        _set_statfp(0x01);
    } else if ((flags & 0x04) && (control & 0x04)) {
        pending &= ~0x04U;
        _set_statfp(0x04);
    } else if ((flags & 0x01) && (control & 0x08)) {
        _set_statfp(0x08);
        switch (control & 0xc00) {
        case 0:
            if (!(*result <= 0.0)) { result_bits->high = _d_inf.words.high; result_bits->low = _d_inf.words.low; }
            else *result = -_d_inf.value;
            pending &= ~0x01U;
            break;
        case 0x400:
            if (!(*result <= 0.0)) { result_bits->high = _d_max.words.high; result_bits->low = _d_max.words.low; }
            else *result = -_d_inf.value;
            pending &= ~0x01U;
            break;
        case 0x800:
            if (!(*result <= 0.0)) { result_bits->high = _d_inf.words.high; result_bits->low = _d_inf.words.low; }
            else *result = -_d_max.value;
            pending &= ~0x01U;
            break;
        case 0xc00:
            if (!(*result <= 0.0)) { result_bits->high = _d_max.words.high; result_bits->low = _d_max.words.low; }
            else *result = -_d_max.value;
            pending &= ~0x01U;
            break;
        default:
            pending &= ~0x01U;
            break;
        }
    } else if ((flags & 0x02) && (control & 0x10)) {
        inexact = 0;
        if (flags & 0x10)
            inexact = 1;
        if (((result_bits->high & 0x7fffffffU) | result_bits->low) != 0) {
            fraction.value = dxball_crt_decompose_double(*result, &exponent);
            adjusted_exponent = exponent - 1536;
            if (adjusted_exponent < -1074) {
                inexact = 1;
                fraction.bits.low = 0;
                fraction.bits.high = 0;
            } else {
                negative = fraction.value < 0.0;
                fraction.words[3] &= 0x000f;
                fraction.bytes[6] |= 0x10;
                if (adjusted_exponent < -1021) {
                    int shift = -1021 - adjusted_exponent;
                    do {
                        if ((fraction.bits.low & 1) && !inexact)
                            inexact = 1;
                        fraction.bits.low >>= 1;
                        if (fraction.bits.high & 1)
                            fraction.bits.low |= 0x80000000U;
                        fraction.bits.high >>= 1;
                    } while (--shift);
                }
                if (negative)
                    fraction.value = -fraction.value;
            }
            result_bits->high = fraction.bits.high;
            result_bits->low = fraction.bits.low;
        } else {
            inexact = 1;
        }
        if (inexact)
            _set_statfp(0x10);
        pending &= ~0x02U;
    }
    if ((flags & 0x10) && (control & 0x20)) {
        pending &= ~0x10U;
        _set_statfp(0x20);
    }
    return pending == 0;
}
