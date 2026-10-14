#include "runtime_stream_operations.h"
#include <string.h>

/* FUNCTION: DXBALL 0x00418310 */
int dxball_crt_fseek(DxBallCrtStream *argument, DxBallCrtLong offset, int origin)
{
    register DxBallCrtStream *stream;
    stream = argument;
    if ((stream->flags & 0x83) == 0 ||
            (origin != 0 && origin != 1 && origin != 2)) {
        errno = 22;
        return -1;
    }
    stream->flags &= ~0x10;
    if (origin == 1) {
        offset += dxball_crt_ftell(stream);
        origin = 0;
    }
    dxball_crt_flush_buffer(stream);
    if (stream->flags & 0x80)
        stream->flags &= ~3;
    else if ((stream->flags & 1) && (stream->flags & 8) &&
            (stream->flags & 0x400) == 0)
        stream->capacity = 512;
    return dxball_crt_seek(stream->descriptor, offset, origin) == -1 ? -1 : 0;
}

/* FUNCTION: DXBALL 0x00417E70 */
unsigned int dxball_crt_fwrite(const void *buffer, unsigned int element_size,
                             unsigned int elements, DxBallCrtStream *stream)
{
    const char *cursor;
    unsigned int total, remaining, capacity, amount, written;
    int value;
    cursor = (const char *)buffer;
    remaining = total = element_size * elements;
    if (remaining == 0) return 0;
    if (stream->flags & 0x10c)
        capacity = (unsigned int)stream->capacity;
    else
        capacity = 4096;
    while (remaining != 0) {
        if ((stream->flags & 0x108) && stream->count != 0) {
            amount = remaining < (unsigned int)stream->count
                ? remaining : (unsigned int)stream->count;
            memcpy(stream->cursor, cursor, amount);
            remaining -= amount;
            stream->count -= amount;
            stream->cursor += amount;
            cursor += amount;
        } else if (remaining >= capacity) {
            if ((stream->flags & 0x108) && dxball_crt_flush_buffer(stream) != 0)
                return (total - remaining) / element_size;
            amount = capacity ? remaining - remaining % capacity : remaining;
            written = (unsigned int)dxball_crt_write(stream->descriptor, cursor, amount);
            if (written == (unsigned int)-1) {
                stream->flags |= 0x20;
                return (total - remaining) / element_size;
            }
            remaining -= written;
            cursor += written;
            if (written < amount) {
                stream->flags |= 0x20;
                return (total - remaining) / element_size;
            }
        } else {
            value = (int)(signed char)*cursor;
            if (dxball_crt_flush_output(value, stream) == -1)
                return (total - remaining) / element_size;
            ++cursor;
            --remaining;
            capacity = stream->capacity > 0 ? (unsigned int)stream->capacity : 1;
        }
    }
    return elements;
}
