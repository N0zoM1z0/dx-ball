#include "runtime_string_concatenation.h"
#include <stddef.h>
#include <string.h>

#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallConcatenationWord {
#else
typedef struct DxBallConcatenationWord {
#endif
    unsigned int value;
} DxBallConcatenationWord;

/* The two original entries share this copy tail. Keep one source block without
   inventing a C-callable address or ABI for the original register-carried tail. */
#define DXBALL_COPY_STRING_TAIL(original, output, input) do { \
    char *copy_destination = (output); \
    const char *copy_source = (input); \
    unsigned int copy_word, copy_candidate; \
    while ((size_t)(const void *)copy_source & 3) { \
        unsigned char copy_byte = (unsigned char)*copy_source++; \
        if (copy_byte == 0) { \
            *copy_destination = 0; \
            return (original); \
        } \
        *copy_destination++ = (char)copy_byte; \
    } \
    for (;;) { \
        copy_word = ((const volatile DxBallConcatenationWord *)(const void *)copy_source)->value; \
        copy_candidate = ((copy_word + 0x7efefeffU) ^ ~copy_word) & 0x81010100U; \
        copy_word = ((const volatile DxBallConcatenationWord *)(const void *)copy_source)->value; \
        copy_source += 4; \
        if (copy_candidate) { \
            if ((copy_word & 0xffU) == 0) { \
                *copy_destination = (char)copy_word; \
                return (original); \
            } \
            if ((copy_word & 0xff00U) == 0) { \
                memcpy(copy_destination, &copy_word, 2); \
                return (original); \
            } \
            if ((copy_word & 0xff0000U) == 0) { \
                memcpy(copy_destination, &copy_word, 2); \
                copy_destination[2] = 0; \
                return (original); \
            } \
            if ((copy_word & 0xff000000U) == 0) { \
                memcpy(copy_destination, &copy_word, 4); \
                return (original); \
            } \
        } \
        memcpy(copy_destination, &copy_word, 4); \
        copy_destination += 4; \
    } \
} while (0)

/* FUNCTION: DXBALL 0x004177F0; shared original extent ends at0x004178D7. */
char *dxball_crt_strcpy(char *destination, const char *source)
{
    DXBALL_COPY_STRING_TAIL(destination, destination, source);
}

/* FUNCTION: DXBALL 0x004177F8 */
char *dxball_crt_strcat(char *destination, const char *source)
{
    char *cursor = destination;
    unsigned int word, candidate;
    while ((size_t)(const void *)cursor & 3) {
        if (*cursor++ == 0) {
            --cursor;
            goto copy_tail;
        }
    }
    for (;;) {
        word = ((const volatile DxBallConcatenationWord *)(const void *)cursor)->value;
        candidate = ((word + 0x7efefeffU) ^ ~word) & 0x81010100U;
        cursor += 4;
        if (candidate) {
            word = ((const volatile DxBallConcatenationWord *)(const void *)(cursor - 4))->value;
            if ((word & 0xffU) == 0) { cursor -= 4; break; }
            if ((word & 0xff00U) == 0) { cursor -= 3; break; }
            if ((word & 0xff0000U) == 0) { cursor -= 2; break; }
            if ((word & 0xff000000U) == 0) { --cursor; break; }
        }
    }
copy_tail:
    DXBALL_COPY_STRING_TAIL(destination, cursor, source);
}

#undef DXBALL_COPY_STRING_TAIL
