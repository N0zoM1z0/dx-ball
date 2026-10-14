#include "runtime_string_copy.h"

char *dxball_crt_strncpy(char *destination, const char *source, size_t count)
{
    char *result = destination;
    while (count) {
        char character = *source++;
        if (!character)
            break;
        *destination++ = character;
        --count;
    }
    while (count) {
        *destination++ = 0;
        --count;
    }
    return result;
}

char *dxball_crt_strncat(char *destination, const char *source, size_t count)
{
    char *result = destination;
    const char *cursor = source;
    size_t copied = 0;
    while (*destination)
        ++destination;
    /* The original scans the bounded source before performing the copy. */
    while (copied < count && *cursor) {
        ++cursor;
        ++copied;
    }
    while (copied) {
        *destination++ = *source++;
        --copied;
    }
    *destination = 0;
    return result;
}
