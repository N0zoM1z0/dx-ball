#include "runtime_ctype_state.h"

enum DxBallCrtCharacterClass {
    CRT_UPPER = 1, CRT_LOWER = 2, CRT_DIGIT = 4, CRT_SPACE = 8,
    CRT_PUNCT = 16, CRT_CONTROL = 32, CRT_BLANK = 64, CRT_HEX = 128
};

/* Independent writable slots initially skip the shared EOF entry. */
unsigned short *_pctype = _ctype + 1;
unsigned short *_pwctype = _ctype + 1;

unsigned short _ctype[257] = {
    0, /* EOF */
    CRT_CONTROL, /* 0x00 */
    CRT_CONTROL, /* 0x01 */
    CRT_CONTROL, /* 0x02 */
    CRT_CONTROL, /* 0x03 */
    CRT_CONTROL, /* 0x04 */
    CRT_CONTROL, /* 0x05 */
    CRT_CONTROL, /* 0x06 */
    CRT_CONTROL, /* 0x07 */
    CRT_CONTROL, /* 0x08 */
    CRT_CONTROL | CRT_SPACE, /* 0x09 */
    CRT_CONTROL | CRT_SPACE, /* 0x0A */
    CRT_CONTROL | CRT_SPACE, /* 0x0B */
    CRT_CONTROL | CRT_SPACE, /* 0x0C */
    CRT_CONTROL | CRT_SPACE, /* 0x0D */
    CRT_CONTROL, /* 0x0E */
    CRT_CONTROL, /* 0x0F */
    CRT_CONTROL, /* 0x10 */
    CRT_CONTROL, /* 0x11 */
    CRT_CONTROL, /* 0x12 */
    CRT_CONTROL, /* 0x13 */
    CRT_CONTROL, /* 0x14 */
    CRT_CONTROL, /* 0x15 */
    CRT_CONTROL, /* 0x16 */
    CRT_CONTROL, /* 0x17 */
    CRT_CONTROL, /* 0x18 */
    CRT_CONTROL, /* 0x19 */
    CRT_CONTROL, /* 0x1A */
    CRT_CONTROL, /* 0x1B */
    CRT_CONTROL, /* 0x1C */
    CRT_CONTROL, /* 0x1D */
    CRT_CONTROL, /* 0x1E */
    CRT_CONTROL, /* 0x1F */
    CRT_SPACE | CRT_BLANK, /* 0x20 */
    CRT_PUNCT, /* 0x21 */
    CRT_PUNCT, /* 0x22 */
    CRT_PUNCT, /* 0x23 */
    CRT_PUNCT, /* 0x24 */
    CRT_PUNCT, /* 0x25 */
    CRT_PUNCT, /* 0x26 */
    CRT_PUNCT, /* 0x27 */
    CRT_PUNCT, /* 0x28 */
    CRT_PUNCT, /* 0x29 */
    CRT_PUNCT, /* 0x2A */
    CRT_PUNCT, /* 0x2B */
    CRT_PUNCT, /* 0x2C */
    CRT_PUNCT, /* 0x2D */
    CRT_PUNCT, /* 0x2E */
    CRT_PUNCT, /* 0x2F */
    CRT_DIGIT | CRT_HEX, /* 0x30 */
    CRT_DIGIT | CRT_HEX, /* 0x31 */
    CRT_DIGIT | CRT_HEX, /* 0x32 */
    CRT_DIGIT | CRT_HEX, /* 0x33 */
    CRT_DIGIT | CRT_HEX, /* 0x34 */
    CRT_DIGIT | CRT_HEX, /* 0x35 */
    CRT_DIGIT | CRT_HEX, /* 0x36 */
    CRT_DIGIT | CRT_HEX, /* 0x37 */
    CRT_DIGIT | CRT_HEX, /* 0x38 */
    CRT_DIGIT | CRT_HEX, /* 0x39 */
    CRT_PUNCT, /* 0x3A */
    CRT_PUNCT, /* 0x3B */
    CRT_PUNCT, /* 0x3C */
    CRT_PUNCT, /* 0x3D */
    CRT_PUNCT, /* 0x3E */
    CRT_PUNCT, /* 0x3F */
    CRT_PUNCT, /* 0x40 */
    CRT_UPPER | CRT_HEX, /* 0x41 */
    CRT_UPPER | CRT_HEX, /* 0x42 */
    CRT_UPPER | CRT_HEX, /* 0x43 */
    CRT_UPPER | CRT_HEX, /* 0x44 */
    CRT_UPPER | CRT_HEX, /* 0x45 */
    CRT_UPPER | CRT_HEX, /* 0x46 */
    CRT_UPPER, /* 0x47 */
    CRT_UPPER, /* 0x48 */
    CRT_UPPER, /* 0x49 */
    CRT_UPPER, /* 0x4A */
    CRT_UPPER, /* 0x4B */
    CRT_UPPER, /* 0x4C */
    CRT_UPPER, /* 0x4D */
    CRT_UPPER, /* 0x4E */
    CRT_UPPER, /* 0x4F */
    CRT_UPPER, /* 0x50 */
    CRT_UPPER, /* 0x51 */
    CRT_UPPER, /* 0x52 */
    CRT_UPPER, /* 0x53 */
    CRT_UPPER, /* 0x54 */
    CRT_UPPER, /* 0x55 */
    CRT_UPPER, /* 0x56 */
    CRT_UPPER, /* 0x57 */
    CRT_UPPER, /* 0x58 */
    CRT_UPPER, /* 0x59 */
    CRT_UPPER, /* 0x5A */
    CRT_PUNCT, /* 0x5B */
    CRT_PUNCT, /* 0x5C */
    CRT_PUNCT, /* 0x5D */
    CRT_PUNCT, /* 0x5E */
    CRT_PUNCT, /* 0x5F */
    CRT_PUNCT, /* 0x60 */
    CRT_LOWER | CRT_HEX, /* 0x61 */
    CRT_LOWER | CRT_HEX, /* 0x62 */
    CRT_LOWER | CRT_HEX, /* 0x63 */
    CRT_LOWER | CRT_HEX, /* 0x64 */
    CRT_LOWER | CRT_HEX, /* 0x65 */
    CRT_LOWER | CRT_HEX, /* 0x66 */
    CRT_LOWER, /* 0x67 */
    CRT_LOWER, /* 0x68 */
    CRT_LOWER, /* 0x69 */
    CRT_LOWER, /* 0x6A */
    CRT_LOWER, /* 0x6B */
    CRT_LOWER, /* 0x6C */
    CRT_LOWER, /* 0x6D */
    CRT_LOWER, /* 0x6E */
    CRT_LOWER, /* 0x6F */
    CRT_LOWER, /* 0x70 */
    CRT_LOWER, /* 0x71 */
    CRT_LOWER, /* 0x72 */
    CRT_LOWER, /* 0x73 */
    CRT_LOWER, /* 0x74 */
    CRT_LOWER, /* 0x75 */
    CRT_LOWER, /* 0x76 */
    CRT_LOWER, /* 0x77 */
    CRT_LOWER, /* 0x78 */
    CRT_LOWER, /* 0x79 */
    CRT_LOWER, /* 0x7A */
    CRT_PUNCT, /* 0x7B */
    CRT_PUNCT, /* 0x7C */
    CRT_PUNCT, /* 0x7D */
    CRT_PUNCT, /* 0x7E */
    CRT_CONTROL, /* 0x7F */
    /* Bytes 0x80 through 0xFF initially have no C-locale classification. */
};
