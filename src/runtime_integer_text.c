#include "runtime_integer_text.h"

/* FUNCTION: DXBALL 0x0041F510 */
static void dxball_crt_xtoa(DxBallIntegerTextWord value, char *buffer,
                           unsigned int radix, int negative)
{
    char *cursor = buffer;
    char *first;
    if (negative) {
        *cursor++ = '-';
        value = 0 - value;
    }
    first = cursor;
    do {
        unsigned int digit = value % radix;
        value /= radix;
        if (digit > 9) *cursor = (char)(digit + 87);
        else *cursor = (char)(digit + '0');
        ++cursor;
    } while (value != 0);
    *cursor = '\0';
    --cursor;
    do {
        char value_at_end = *cursor;
        *cursor = *first;
        --cursor;
        *first = value_at_end;
        ++first;
    } while (first < cursor);
}

/* FUNCTION: DXBALL 0x0041F4D0 */
char *dxball_crt_itoa(int value, char *buffer, int radix)
{
    if (radix == 10 && value < 0) {
        dxball_crt_xtoa((DxBallIntegerTextWord)value, buffer, (unsigned int)radix, 1);
        return buffer;
    }
    dxball_crt_xtoa((DxBallIntegerTextWord)value, buffer, (unsigned int)radix, 0);
    return buffer;
}

/* FUNCTION: DXBALL 0x0041F570 */
char *dxball_crt_ultoa(DxBallIntegerTextWord value, char *buffer, int radix)
{
    dxball_crt_xtoa(value, buffer, (unsigned int)radix, 0);
    return buffer;
}
