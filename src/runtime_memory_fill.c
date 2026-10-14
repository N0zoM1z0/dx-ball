#include "runtime_memory_fill.h"

#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallFillWord {
#else
typedef struct DxBallFillWord {
#endif
    unsigned int value;
} DxBallFillWord;

void *dxball_crt_fill_memory(void *destination, int value, size_t count)
{
    unsigned char *cursor = (unsigned char *)destination;
    unsigned int word = (unsigned char)value;
    size_t prefix, words;
    if (count == 0)
        return destination;
    if (count >= 4) {
        prefix = (0 - (size_t)(void *)cursor) & 3;
        count -= prefix;
        while (prefix) {
            *cursor++ = (unsigned char)word;
            --prefix;
        }
        word = (word << 8) + word;
        word = (word << 16) + word;
        words = count >> 2;
        count &= 3;
        while (words) {
            ((DxBallFillWord *)(void *)cursor)->value = word;
            cursor += 4;
            --words;
        }
    }
    while (count) {
        *cursor++ = (unsigned char)word;
        --count;
    }
    return destination;
}
