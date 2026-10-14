#include "runtime_stream_operations.h"
#include <string.h>

/* FUNCTION: DXBALL 0x00418310 */
int dxball_crt_fseek(DxBallCrtStream *stream, DxBallCrtLong offset, int origin)
{
    if ((stream->flags & 0x83) == 0 ||
            (origin != 0 && origin != 1 && origin != 2)) {
        errno = 22;
        return -1;
    }
    stream->flags &= ~0x10;
    if (origin == 1) {
        origin = 0;
        offset += dxball_crt_ftell(stream);
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
    const char *cursor = (const char *)buffer;
    unsigned int total = element_size * elements;
    unsigned int remaining = total;
    unsigned int capacity;
    if (total == 0) return 0;
    capacity = stream->flags & 0x10c ? (unsigned int)stream->capacity : 4096;
    while (remaining != 0) {
        if ((stream->flags & 0x108) && stream->count != 0) {
            unsigned int available = (unsigned int)stream->count;
            unsigned int amount = remaining < available ? remaining : available;
            remaining -= amount;
            memcpy(stream->cursor, cursor, amount);
            stream->count -= amount;
            stream->cursor += amount;
            cursor += amount;
        } else if (remaining >= capacity) {
            unsigned int amount;
            int written;
            if ((stream->flags & 0x108) && dxball_crt_flush_buffer(stream) != 0)
                return (total - remaining) / element_size;
            amount = capacity ? remaining - remaining % capacity : remaining;
            written = dxball_crt_write(stream->descriptor, cursor, amount);
            if (written == -1) {
                stream->flags |= 0x20;
                return (total - remaining) / element_size;
            }
            remaining -= (unsigned int)written;
            cursor += written;
            if ((unsigned int)written < amount) {
                stream->flags |= 0x20;
                return (total - remaining) / element_size;
            }
        } else {
            if (dxball_crt_flush_output((int)(signed char)*cursor, stream) == -1)
                return (total - remaining) / element_size;
            --remaining;
            ++cursor;
            capacity = (unsigned int)stream->capacity;
            if ((int)capacity <= 0) capacity = 1;
        }
    }
    return elements;
}
