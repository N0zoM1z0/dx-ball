#include "runtime_decimal.h"

/* The intermediate product is a 96-bit integer until the final exponent
   is inserted. The packed view exposes its retained 80 bits above the guard. */
typedef union DxBallProduct96 {
    unsigned int words[3];
    unsigned short halves[6];
    unsigned char bytes[12];
    DxBallExtended12 packed;
} DxBallProduct96;

/* FUNCTION: DXBALL 0x0041F990 */
void __ld12mul(DxBallExtended12 *left, const DxBallExtended12 *right)
{
    DxBallProduct96 product;
    unsigned int *left_words = (unsigned int *)left;
    const unsigned int *right_words = (const unsigned int *)right;
    const unsigned short *left_halves = (const unsigned short *)left;
    const unsigned short *right_halves = (const unsigned short *)right;
    unsigned short left_exponent = left->exponent;
    unsigned short right_exponent = right->exponent;
    unsigned short sign = (left_exponent ^ right_exponent) & 0x8000;
    unsigned short exponent;
    int diagonal, product_offset;
    product.words[0] = 0;
    product.words[1] = 0;
    product.words[2] = 0;
    left_exponent &= 0x7fff;
    right_exponent &= 0x7fff;
    exponent = left_exponent + right_exponent;
    if (left_exponent >= 0x7fff || right_exponent >= 0x7fff || exponent > 0xbffd) {
        left_words[1] = 0;
        left_words[0] = 0;
        left_words[2] = (sign == 0 ? 0x80000000U : 0U) - 0x8000;
        return;
    }
    if (exponent < 0x3fc0) {
        left_words[2] = 0;
        left_words[1] = 0;
        left_words[0] = 0;
        return;
    }
    if (left_exponent == 0) {
        ++exponent;
        if ((left_words[2] & 0x7fffffffU) == 0 && left_words[1] == 0 && left_words[0] == 0) {
            left->exponent = 0;
            return;
        }
    }
    if (right_exponent == 0) {
        ++exponent;
        if ((right_words[2] & 0x7fffffffU) == 0 && right_words[1] == 0 && right_words[0] == 0) {
            left_words[2] = 0;
            left_words[1] = 0;
            left_words[0] = 0;
            return;
        }
    }
    for (product_offset = 0, diagonal = 0; diagonal < 5;
            product_offset += sizeof(product.halves[0]), ++diagonal) {
        int left_offset = diagonal * sizeof(*left_halves);
        int right_offset = 4 * sizeof(*right_halves);
        int remaining = 5 - diagonal;
        unsigned int *accumulator = (unsigned int *)(product.bytes + product_offset);
        if (remaining > 0) do {
            unsigned int term = (unsigned int)*(const unsigned short *)
                ((const unsigned char *)left_halves + left_offset) *
                *(const unsigned short *)((const unsigned char *)right_halves + right_offset);
            if (__addl(*accumulator, term, accumulator))
                ++*(unsigned short *)(product.bytes + product_offset + sizeof(product.words[0]));
            left_offset += sizeof(*left_halves);
            right_offset -= sizeof(*right_halves);
        } while (--remaining);
    }
    exponent -= 0x3ffe;
    while ((short)exponent > 0 && (product.words[2] & 0x80000000U) == 0) {
        __shl_12(product.words);
        --exponent;
    }
    if ((short)exponent <= 0) {
        unsigned int sticky;
        --exponent;
        if ((short)exponent < 0) {
            unsigned short shifts = (unsigned short)-(short)exponent;
            sticky = product.words[0];
            exponent += shifts;
            do {
                if (product.halves[0] & 1) ++sticky;
                __shr_12(product.words);
            } while (--shifts);
        } else {
            sticky = product.words[0];
        }
        if (sticky != 0) product.bytes[0] |= 1;
    }
    if (product.packed.extra > 0x8000) {
        if (product.packed.low == ~0U) {
            product.packed.low = 0;
            if (product.packed.high == ~0U) {
                product.packed.high = 0;
                if (product.packed.exponent == 0xffff) {
                    product.packed.exponent = 0x8000;
                    ++exponent;
                } else {
                    ++product.packed.exponent;
                }
            } else {
                ++product.packed.high;
            }
        } else {
            ++product.packed.low;
        }
    }
    if (exponent >= 0x7fff) {
        left_words[1] = 0;
        left_words[0] = 0;
        left_words[2] = (sign == 0 ? 0x80000000U : 0U) - 0x8000;
    } else {
        left->extra = product.halves[1];
        left->low = product.words[1];
        left->high = product.words[2];
        left->exponent = sign | exponent;
    }
}

/* FUNCTION: DXBALL 0x0041FC40 */
void __multtenpow12(DxBallExtended12 *value, int exponent, int keep_tail)
{
    const DxBallExtended12 *powers = _pow10pos;
    int group = -8;
    if (exponent != 0) {
        if (exponent < 0) {
            exponent = -exponent;
            powers = _pow10neg;
        }
        if (!keep_tail) value->extra = 0;
        while (exponent != 0) {
            int index;
            group += 7;
            index = exponent & 7;
            exponent >>= 3;
            if (index != 0) {
                DxBallExtended12 corrected;
                const DxBallExtended12 *power = &powers[group + index];
                if (power->extra >= 0x8000) {
                    corrected = *power;
                    --corrected.low;
                    power = &corrected;
                }
                __ld12mul(value, power);
            }
        }
    }
}

#define DXBALL_DECIMAL_DIGIT(c) \
    (__mb_cur_max > 1 ? _isctype((unsigned char)(c), 4) : \
     (_pctype[(unsigned char)(c)] & 4))

/* FUNCTION: DXBALL 0x0041E7D0 */
int _strgtold12(DxBallExtended12 *value, const char **end, const char *text,
                int keep_tail, int decimal_exponent, int fractional_digits,
                int allow_implicit_exponent)
{
    enum { START, LEADING_ZERO, AFTER_SIGN, INTEGER, FRACTION, AFTER_POINT,
           AFTER_EXPONENT, EXPONENT_SIGN, EXPONENT_ZERO, EXPONENT_DIGITS,
           DONE, IMPLICIT_EXPONENT };
    char digits[25];
    char *next_digit = digits;
    const char *cursor = text;
    const char *rollback = text;
    unsigned int count = 0;
    unsigned short sign = 0;
    int state = START;
    int seen_digit = 0, seen_point = 0, seen_exponent = 0;
    int exponent_sign = 1, exponent = 0, adjustment = 0;
    int overflow = 0, underflow = 0, status = 0;
    unsigned short extra, output_exponent;
    unsigned int low, high;
    DxBallProduct96 converted;
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' || *cursor == '\r') ++cursor;
    do {
        char character = *cursor++;
        switch (state) {
        case START:
            if (character >= '1' && character <= '9') {
                state = INTEGER;
                goto reprocess;
            }
            if (character == __decimal_point) {
                state = AFTER_POINT;
            } else if (character == '+') {
                sign = 0;
                state = AFTER_SIGN;
            } else if (character == '-') {
                sign = 0x8000;
                state = AFTER_SIGN;
            } else if (character == '0') {
                state = LEADING_ZERO;
            } else {
                goto finish;
            }
            break;
        case LEADING_ZERO:
            seen_digit = 1;
            if (character >= '1' && character <= '9') {
                state = INTEGER;
                goto reprocess;
            }
            if (character == __decimal_point) {
                state = FRACTION;
            } else {
                switch (character) {
                case '+': case '-':
                    state = IMPLICIT_EXPONENT;
                    goto reprocess;
                case '0':
                    state = LEADING_ZERO;
                    break;
                case 'D': case 'E': case 'd': case 'e':
                    state = AFTER_EXPONENT;
                    break;
                default:
                    goto finish;
                }
            }
            break;
        case AFTER_SIGN:
            if (character >= '1' && character <= '9') {
                state = INTEGER;
                goto reprocess;
            }
            if (character == __decimal_point) {
                state = AFTER_POINT;
            } else if (character == '0') {
                state = LEADING_ZERO;
            } else {
                state = DONE;
                cursor = rollback;
            }
            break;
        case INTEGER:
            seen_digit = 1;
            while (DXBALL_DECIMAL_DIGIT(character)) {
                if (count < 25) {
                    ++count;
                    *next_digit++ = character - '0';
                } else {
                    ++adjustment;
                }
                character = *cursor++;
            }
            if (character == __decimal_point) {
                state = FRACTION;
            } else {
                switch (character) {
                case '+': case '-':
                    state = IMPLICIT_EXPONENT;
                    goto reprocess;
                case 'D': case 'E': case 'd': case 'e':
                    state = AFTER_EXPONENT;
                    break;
                default:
                    goto finish;
                }
            }
            break;
        case FRACTION:
            seen_digit = 1;
            seen_point = 1;
            if (count == 0) {
                while (character == '0') {
                    --adjustment;
                    character = *cursor++;
                }
            }
            while (DXBALL_DECIMAL_DIGIT(character)) {
                if (count < 25) {
                    ++count;
                    --adjustment;
                    *next_digit++ = character - '0';
                }
                character = *cursor++;
            }
            switch (character) {
            case '+': case '-':
                state = IMPLICIT_EXPONENT;
                goto reprocess;
            case 'D': case 'E': case 'd': case 'e':
                state = AFTER_EXPONENT;
                break;
            default:
                goto finish;
            }
            break;
        case AFTER_POINT:
            seen_point = 1;
            if (DXBALL_DECIMAL_DIGIT(character)) {
                state = FRACTION;
                goto reprocess;
            }
            state = DONE;
            cursor = rollback;
            break;
        case AFTER_EXPONENT:
            rollback = cursor - 2;
            if (character >= '1' && character <= '9') {
                state = EXPONENT_DIGITS;
                goto reprocess;
            }
            if (character == '+') {
                state = EXPONENT_SIGN;
            } else if (character == '-') {
                exponent_sign = -1;
                state = EXPONENT_SIGN;
            } else if (character == '0') {
                state = EXPONENT_ZERO;
            } else {
                state = DONE;
                cursor = rollback;
            }
            break;
        case EXPONENT_SIGN:
            if (character >= '1' && character <= '9') {
                state = EXPONENT_DIGITS;
                goto reprocess;
            }
            if (character == '0') {
                state = EXPONENT_ZERO;
            } else {
                state = DONE;
                cursor = rollback;
            }
            break;
        case EXPONENT_ZERO:
            seen_exponent = 1;
            while (character == '0') character = *cursor++;
            if (character >= '1' && character <= '9') {
                state = EXPONENT_DIGITS;
                goto reprocess;
            }
            goto finish;
        case EXPONENT_DIGITS:
            seen_exponent = 1;
            exponent = 0;
            while (DXBALL_DECIMAL_DIGIT(character)) {
                exponent = character - '0' + exponent * 10;
                if (exponent > 0x1450) {
                    exponent = 0x1451;
                    break;
                }
                character = *cursor++;
            }
            while (DXBALL_DECIMAL_DIGIT(character)) character = *cursor++;
            goto finish;
        case IMPLICIT_EXPONENT:
            if (!allow_implicit_exponent) goto finish;
            rollback = cursor - 1;
            if (character == '+') {
                state = EXPONENT_SIGN;
            } else if (character == '-') {
                exponent_sign = -1;
                state = EXPONENT_SIGN;
            } else {
                state = DONE;
                cursor = rollback;
            }
            break;
        }
        continue;
finish:
        state = DONE;
reprocess:
        --cursor;
    } while (state != DONE);
    *end = cursor;
    if (seen_digit) {
        if (count > 24) {
            if (digits[23] >= 5) ++digits[23];
            --next_digit;
            ++adjustment;
            count = 24;
        }
        if (count != 0) {
            --next_digit;
            while (*next_digit == 0) {
                --next_digit;
                --count;
                ++adjustment;
            }
            __mtold12(digits, count, &converted.packed);
            if (exponent_sign < 0) exponent = -exponent;
            exponent += adjustment;
            if (!seen_exponent) exponent += decimal_exponent;
            if (!seen_point) exponent -= fractional_digits;
            if (exponent > 0x1450) {
                overflow = 1;
            } else if (exponent < -0x1450) {
                underflow = 1;
            } else {
                __multtenpow12(&converted.packed, exponent, keep_tail);
                extra = converted.packed.extra;
                low = converted.packed.low;
                high = converted.packed.high;
                output_exponent = converted.packed.exponent;
            }
        } else {
            extra = 0;
            low = 0;
            high = 0;
            output_exponent = 0;
        }
    }
    if (!seen_digit) {
        extra = 0;
        low = 0;
        high = 0;
        output_exponent = 0;
        status = 4;
    } else if (overflow) {
        output_exponent = 0x7fff;
        high = 0x80000000U;
        extra = 0;
        low = 0;
        status = 2;
    } else if (underflow) {
        extra = 0;
        low = 0;
        high = 0;
        output_exponent = 0;
        status = 1;
    }
    value->low = low;
    value->extra = extra;
    value->high = high;
    value->exponent = output_exponent | sign;
    return status;
}
