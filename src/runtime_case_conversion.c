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
    int length;
    unsigned short classification;
    char input[3];
    if ((unsigned int)character + 1 <= 256) return _pctype[character] & mask;
    if (_pctype[(unsigned char)((character >> 8) & 0xff)] & 0x8000) {
        input[0] = (char)((character >> 8) & 0xff);
        input[1] = (char)character;
        input[2] = 0;
        length = 2;
    } else {
        input[0] = (char)character;
        input[1] = 0;
        length = 1;
    }
    if (!__crtGetStringTypeA(1, input, length, &classification, 0, 0))
        return 0;
    return classification & mask;
}
