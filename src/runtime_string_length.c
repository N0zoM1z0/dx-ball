#include "runtime_string_length.h"

#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallStringWord {
#else
typedef struct DxBallStringWord {
#endif
    unsigned int value;
} DxBallStringWord;

size_t dxball_crt_string_length(const char *text)
{
    const char *cursor = text;
    unsigned int word, candidate;
    while ((size_t)(const void *)cursor & 3) {
        if (*cursor == 0)
            return (size_t)(cursor - text);
        ++cursor;
    }
    for (;;) {
        /* The confirmed source word is physically read again after the coarse
           zero-byte test; do not invent a cached or widened string object. */
        word = ((const volatile DxBallStringWord *)(const void *)cursor)->value;
        candidate = ((word + 0x7efefeffU) ^ ~word) & 0x81010100U;
        cursor += 4;
        if (candidate) {
            word = ((const volatile DxBallStringWord *)(const void *)(cursor - 4))->value;
            if ((word & 0xffU) == 0)
                return (size_t)(cursor - 4 - text);
            if ((word & 0xff00U) == 0)
                return (size_t)(cursor - 3 - text);
            if ((word & 0xff0000U) == 0)
                return (size_t)(cursor - 2 - text);
            if ((word & 0xff000000U) == 0)
                return (size_t)(cursor - 1 - text);
        }
    }
}
