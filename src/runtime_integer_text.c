#include "runtime_integer_text.h"

/* FUNCTION: DXBALL 0x0041F510 */
static void dxball_crt_xtoa(DxBallIntegerTextWord value, char *buffer,
                           unsigned int radix, int negative)
{
    char *cursor = buffer;
    size_t first_address;
    size_t end_address;
    if (negative) {
        *cursor++ = '-';
        value = 0 - value;
    }
    first_address = (size_t)cursor;
    do {
        unsigned int digit = value % radix;
        value /= radix;
        if (digit > 9) *cursor = (char)(digit + 87);
        else *cursor = (char)(digit + '0');
        ++cursor;
    } while (value != 0);
    *cursor = '\0';
    /* The final decrement may cross the first character, but is never dereferenced. */
    end_address = (size_t)cursor - 1;
    do {
        char value_at_end = *(char *)end_address;
        *(char *)end_address = *(char *)first_address;
        --end_address;
        *(char *)first_address = value_at_end;
        ++first_address;
    } while (first_address < end_address);
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
