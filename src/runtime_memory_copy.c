#include "runtime_memory_copy.h"

#pragma pack(push, 1)
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallCopyWord {
#else
typedef struct DxBallCopyWord {
#endif
    unsigned int value;
} DxBallCopyWord;
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallCopyHalf {
#else
typedef struct DxBallCopyHalf {
#endif
    unsigned short value;
} DxBallCopyHalf;
#pragma pack(pop)

void *dxball_crt_copy_memory(void *destination, const void *source, size_t count)
{
    unsigned char *output = (unsigned char *)destination;
    const unsigned char *input = (const unsigned char *)source;
    size_t prefix, words;
    if (((size_t)(void *)output & 3) && count <= 12) {
        while (count) {
            *output++ = *input++;
            --count;
        }
        return destination;
    }
    prefix = (0 - (size_t)(void *)output) & 3;
    count -= prefix;
    while (prefix) {
        *output++ = *input++;
        --prefix;
    }
    words = count >> 2;
    count &= 3;
    while (words) {
        ((DxBallCopyWord *)(void *)output)->value =
            ((const DxBallCopyWord *)(const void *)input)->value;
        output += 4;
        input += 4;
        --words;
    }
    if (count >= 2) {
        ((DxBallCopyHalf *)(void *)output)->value =
            ((const DxBallCopyHalf *)(const void *)input)->value;
        output += 2;
        input += 2;
        count -= 2;
    }
    if (count)
        *output = *input;
    return destination;
}
