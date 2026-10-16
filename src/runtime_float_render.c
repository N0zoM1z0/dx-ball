#include "runtime_float_render.h"
#include "runtime_locale_state.h"
#include <string.h>

static char g_format = 0;
static int g_magnitude = 0;
static char g_round_expansion = 0;
static DxBallCrtFloatText *g_float;

char *dxball_crt_format_exponent(const double *value, char *buffer,
                                int precision, int capitals)
{
    DxBallCrtFloatText *digits;
    char *cursor, *exponent_text;
    int exponent;
    if (g_format) {
        digits = g_float;
        cursor = buffer + (digits->sign == '-');
        dxball_crt_shift_float_text(cursor, precision > 0);
    } else {
        digits = dxball_crt_float_output(*value);
        dxball_crt_float_digits(buffer + (digits->sign == '-') + (precision > 0),
                                precision + 1, digits);
    }
    cursor = buffer;
    if (digits->sign == '-')
        *cursor++ = '-';
    if (precision > 0) {
        *cursor = cursor[1];
        *++cursor = __decimal_point[0];
    }
    /* Cold conversion contributes one extra significant digit before the
       precision-sized fractional tail and its exponent suffix. */
    exponent_text = cursor + !g_format;
    exponent_text += precision;
    strcpy(exponent_text, "e+000");
    cursor += precision + !g_format;
    if (capitals)
        *cursor = 'E';
    ++cursor;
    if (*digits->mantissa != '0') {
        exponent = digits->decimal_position - 1;
        if (exponent < 0) {
            exponent = -exponent;
            *cursor = '-';
        }
        ++cursor;
        if (exponent >= 100) {
            *cursor += (char)(exponent / 100);
            exponent %= 100;
        }
        ++cursor;
        if (exponent >= 10) {
            *cursor += (char)(exponent / 10);
            exponent %= 10;
        }
        cursor[1] += (char)exponent;
    }
    return buffer;
}

char *dxball_crt_format_fixed(const double *value, char *buffer, int precision)
{
    DxBallCrtFloatText *digits;
    char *cursor;
    int zeros;
    if (g_format) {
        digits = g_float;
        cursor = buffer + (digits->sign == '-');
        if (g_magnitude == precision) {
            cursor += g_magnitude;
            *cursor = '0';
            cursor[1] = 0;
        }
    } else {
        digits = dxball_crt_float_output(*value);
        dxball_crt_float_digits(buffer + (digits->sign == '-'),
                                digits->decimal_position + precision, digits);
    }
    cursor = buffer;
    if (digits->sign == '-')
        *cursor++ = '-';
    if (digits->decimal_position <= 0) {
        dxball_crt_shift_float_text(cursor, 1);
        *cursor++ = '0';
    } else {
        cursor += digits->decimal_position;
    }
    if (precision > 0) {
        dxball_crt_shift_float_text(cursor, 1);
        *cursor++ = __decimal_point[0];
        if (digits->decimal_position < 0) {
            if (g_format) {
                zeros = -digits->decimal_position;
            } else {
                zeros = -digits->decimal_position < precision ?
                    -digits->decimal_position : precision;
            }
            dxball_crt_shift_float_text(cursor, zeros);
            memset(cursor, '0', zeros);
        }
    }
    return buffer;
}

void dxball_crt_format_general(const double *value, char *buffer,
                              int precision, int capitals)
{
    char *digits;
    g_float = dxball_crt_float_output(*value);
    g_magnitude = g_float->decimal_position - 1;
    digits = buffer + (g_float->sign == '-');
    dxball_crt_float_digits(digits, precision, g_float);
    g_round_expansion = g_magnitude < g_float->decimal_position - 1;
    g_magnitude = g_float->decimal_position - 1;
    if (g_magnitude < -4 || g_magnitude >= precision) {
        dxball_crt_format_general_exponent(value, buffer, precision, capitals);
        return;
    }
    if (g_round_expansion) {
        while (*digits++) {}
        digits[-2] = 0;
    }
    dxball_crt_format_general_fixed(value, buffer, precision);
}

void dxball_crt_format_general_exponent(const double *value, char *buffer,
                                       int precision, int capitals)
{
    g_format = 1;
    dxball_crt_format_exponent(value, buffer, precision, capitals);
    g_format = 0;
}

void dxball_crt_format_general_fixed(const double *value, char *buffer, int precision)
{
    g_format = 1;
    dxball_crt_format_fixed(value, buffer, precision);
    g_format = 0;
}

void dxball_crt_shift_float_text(char *buffer, int shift)
{
    if (shift)
        memmove(buffer + shift, buffer, strlen(buffer) + 1);
}
