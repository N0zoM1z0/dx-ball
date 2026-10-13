#include "runtime_case_conversion.h"

/* FUNCTION: DXBALL 0x00418040 */
int dxball_crt_toupper(int character)
{
    unsigned char input[3];
    unsigned char output[3];
    int length;
    int mapped;
    if (__lc_handle[2] == 0) {
        if (character >= 'a' && character <= 'z') character -= 'a' - 'A';
        return character;
    }
    if (character < 256 && !(__mb_cur_max > 1 ? _isctype(character, 2) :
                                              _pctype[character] & 2))
        return character;
    if (_pctype[(unsigned char)((unsigned int)character >> 8)] & 0x8000) {
        length = 2;
        input[0] = (unsigned char)((unsigned int)character >> 8);
        input[2] = 0;
        input[1] = (unsigned char)character;
    } else {
        length = 1;
        input[0] = (unsigned char)character;
        input[1] = 0;
    }
    mapped = __crtLCMapStringA(__lc_handle[2], 0x200, (const char *)input,
                              length, (char *)output, 3, 0);
    if (mapped == 0) return character;
    if (mapped == 1) return output[0];
    return (output[1] << 8) | output[0];
}

/* FUNCTION: DXBALL 0x00418130 */
int dxball_crt_tolower(int character)
{
    unsigned char input[3];
    unsigned char output[3];
    int length;
    int mapped;
    if (__lc_handle[2] == 0) {
        if (character >= 'A' && character <= 'Z') character += 'a' - 'A';
        return character;
    }
    if (character < 256 && !(__mb_cur_max > 1 ? _isctype(character, 1) :
                                              _pctype[character] & 1))
        return character;
    if (_pctype[(unsigned char)((unsigned int)character >> 8)] & 0x8000) {
        length = 2;
        input[0] = (unsigned char)((unsigned int)character >> 8);
        input[2] = 0;
        input[1] = (unsigned char)character;
    } else {
        length = 1;
        input[0] = (unsigned char)character;
        input[1] = 0;
    }
    mapped = __crtLCMapStringA(__lc_handle[2], 0x100, (const char *)input,
                              length, (char *)output, 3, 0);
    if (mapped == 0) return character;
    if (mapped == 1) return output[0];
    return (output[1] << 8) | output[0];
}

/* FUNCTION: DXBALL 0x0041AC70 */
int _isctype(int character, int mask)
{
    unsigned char input[3];
    unsigned short classification;
    unsigned char high;
    int length;
    if ((unsigned int)character + 1 <= 256) return _pctype[character] & mask;
    high = (unsigned char)((unsigned int)character >> 8);
    if (_pctype[high] & 0x8000) {
        length = 2;
        input[0] = high;
        input[2] = 0;
        input[1] = (unsigned char)character;
    } else {
        length = 1;
        input[0] = (unsigned char)character;
        input[1] = 0;
    }
    if (!__crtGetStringTypeA(1, (const char *)input, length, &classification, 0, 0))
        return 0;
    return classification & mask;
}
