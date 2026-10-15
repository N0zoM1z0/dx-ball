#include "runtime_float_format.h"
#include "runtime_fatal.h"
#include "runtime_case_conversion.h"
#include <string.h>

extern char __decimal_point;

void dxball_crt_float_unavailable(void)
{
    dxball_crt_amsg_exit(2);
}

void dxball_crt_format_float(const double *value, char *buffer,
                              int format, int precision, int capitals)
{
    if (format == 'e' || format == 'E')
        dxball_crt_format_exponent(value, buffer, precision, capitals);
    else if (format == 'f')
        dxball_crt_format_fixed(value, buffer, precision);
    else
        dxball_crt_format_general(value, buffer, precision, capitals);
}

void dxball_crt_force_decimal_point(char *buffer)
{
    char carried, next, written;
    if (dxball_crt_tolower(*buffer) != 'e') {
        do {
            ++buffer;
        } while ((__mb_cur_max > 1 ? _isctype(*buffer, 4) : _pctype[(int)*buffer] & 4));
    }
    carried = *buffer;
    *buffer++ = __decimal_point;
    do {
        /* Insertion backing includes this defined spare byte after the NUL. */
        next = *buffer;
        written = carried;
        *buffer = written;
        carried = next;
        ++buffer;
    } while (written);
}

void dxball_crt_crop_float_zeros(char *buffer)
{
    size_t cursor = (size_t)(void *)buffer;
    size_t end;
    char character;
    while (*(char *)cursor && *(char *)cursor != __decimal_point)
        ++cursor;
    end = cursor++;
    if (*(char *)end == 0)
        return;
    while (*(char *)cursor && *(char *)cursor != 'e' && *(char *)cursor != 'E')
        ++cursor;
    end = cursor;
    --cursor;
    while (*(char *)cursor == '0')
        --cursor;
    if (*(char *)cursor == __decimal_point)
        --cursor;
    /* A leading decimal point can leave an address cursor before the buffer.
       It is incremented back into the object before forming a write pointer. */
    do {
        character = *(char *)end;
        ++cursor;
        ++end;
        *(char *)cursor = character;
    } while (character);
}

void dxball_crt_assign_float(int use_double, void *destination, const char *text)
{
    union {
        double value;
        struct { unsigned int low, high; } words;
    } double_value;
    float float_value;
    if (use_double) {
        dxball_ascii_to_double(&double_value.value, text);
        /* Preserve both binary64 words without an x87 load or NaN conversion. */
        memcpy(destination, &double_value.words.low, sizeof(double_value.words.low));
        memcpy((char *)destination + sizeof(double_value.words.low),
            &double_value.words.high, sizeof(double_value.words.high));
    } else {
        dxball_ascii_to_float(&float_value, text);
        memcpy(destination, &float_value, sizeof(float_value));
    }
}

int dxball_crt_float_positive(const double *value)
{
    /* Original zero and unordered comparisons are both classified true. */
    return !(*value < 0.0);
}

void dxball_crt_float_digits(char *buffer, int digits, register DxBallCrtFloatText *value)
{
    register char *output = buffer;
    register const char *mantissa = value->mantissa;
    *output++ = '0';
    while (digits > 0) {
        *output++ = *mantissa ? *mantissa++ : '0';
        --digits;
    }
    *output = 0;
    if (digits >= 0 && *mantissa >= '5') {
        --output;
        while (*output == '9') {
            *output-- = '0';
        }
        ++*output;
    }
    if (*buffer == '1')
        ++value->decimal_position;
    else
        /* Preserve the shipped CRT operation, including its overlapping input. */
        strcpy(buffer, buffer + 1);
}
