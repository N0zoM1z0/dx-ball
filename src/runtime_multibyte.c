#include "runtime_multibyte.h"

static int dxball_crt_ismbbtype(unsigned int character, int ctype_mask, int mb_mask)
{
    unsigned char byte = (unsigned char)character;
    if ((_mbctype[byte + 1] & mb_mask) ||
        (ctype_mask ? (_ctype[byte + 1] & ctype_mask) : 0))
        return 1;
    return 0;
}

int dxball_crt_ismbblead(unsigned int character)
{
    return dxball_crt_ismbbtype(character, 0, 4);
}
