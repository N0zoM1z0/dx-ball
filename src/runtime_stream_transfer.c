#include "runtime_stream_transfer.h"
#include <string.h>

/* FUNCTION: DXBALL 0x00417A30 */
int dxball_crt_fclose(DxBallCrtStream *stream)
{
    int status = -1;
    if (stream->flags & 0x40) {
        stream->flags = 0;
        return status;
    }
    if (stream->flags & 0x83) {
        status = dxball_crt_flush_buffer(stream);
        dxball_crt_free_buffer(stream);
        if (dxball_crt_close(stream->descriptor) < 0) status = -1;
        else if (stream->temporary_name != NULL) {
            dxball_heap_release(stream->temporary_name);
            stream->temporary_name = NULL;
        }
    }
    stream->flags = 0;
    return status;
}

/* FUNCTION: DXBALL 0x0041A5A0 */
DxBallCrtStream *dxball_crt_get_stream(void)
{
    DxBallCrtStream *stream = NULL;
    int index;
    for (index = 0; index < dxball_crt_stream_limit; ++index) {
        if (dxball_crt_streams[index] != NULL) {
            if ((dxball_crt_streams[index]->flags & 0x83) == 0) {
                stream = dxball_crt_streams[index];
                break;
            }
        } else {
            dxball_crt_streams[index] = (DxBallCrtStream *)dxball_runtime_malloc(sizeof(*stream));
            if (dxball_crt_streams[index] != NULL) stream = dxball_crt_streams[index];
            break;
        }
    }
    if (stream != NULL) {
        stream->count = 0;
        stream->flags = 0;
        stream->buffer = NULL;
        stream->cursor = NULL;
        stream->temporary_name = NULL;
        stream->descriptor = -1;
    }
    return stream;
}

/* FUNCTION: DXBALL 0x0041DFA0 */
int dxball_crt_isatty(int descriptor)
{
    return (unsigned int)descriptor < (unsigned int)_nhandle
        ? (int)(signed char)__pioinfo[descriptor >> 5][descriptor & 31].flags & 0x40
        : 0;
}

/* FUNCTION: DXBALL 0x00418220 */
int dxball_crt_fill_input(DxBallCrtStream *argument)
{
    register DxBallCrtStream *stream;
    stream = argument;
    if ((stream->flags & 0x83) == 0 || (stream->flags & 0x40)) return -1;
    if (stream->flags & 2) {
        stream->flags |= 0x20;
        return -1;
    }
    stream->flags |= 1;
    if ((stream->flags & 0x10c) == 0) dxball_crt_get_buffer(stream);
    else stream->cursor = stream->buffer;
    stream->count = dxball_crt_read(stream->descriptor, stream->buffer, stream->capacity);
    if (stream->count == 0 || stream->count == -1) {
        stream->flags |= stream->count ? 0x20 : 0x10;
        stream->count = 0;
        return -1;
    }
    if ((stream->flags & 0x82) == 0) {
        DxBallLowioRecord *record = stream->descriptor == -1
            ? &dxball_crt_invalid_io
            : &__pioinfo[stream->descriptor >> 5][stream->descriptor & 31];
        if ((record->flags & 0x82) == 0x82) stream->flags |= 0x2000;
    }
    if (stream->capacity == 512 && (stream->flags & 8) && (stream->flags & 0x400) == 0)
        stream->capacity = 4096;
    --stream->count;
    return (unsigned char)*stream->cursor++;
}

/* FUNCTION: DXBALL 0x0041A620 */
int dxball_crt_flush_output(int value, DxBallCrtStream *argument)
{
    register DxBallCrtStream *stream;
    register int expected;
    register int written;
    int descriptor;
    stream = argument;
    descriptor = stream->descriptor;
    if ((stream->flags & 0x82) == 0 || (stream->flags & 0x40)) {
        stream->flags |= 0x20;
        return -1;
    }
    if (stream->flags & 1) {
        stream->count = 0;
        if (stream->flags & 0x10) {
            stream->cursor = stream->buffer;
            stream->flags &= ~1;
        } else {
            stream->flags |= 0x20;
            return -1;
        }
    }
    stream->flags |= 2;
    stream->flags &= ~0x10;
    written = expected = stream->count = 0;
    if ((stream->flags & 0x10c) == 0) {
        if (!((stream == &dxball_crt_standard_streams[1] ||
               stream == &dxball_crt_standard_streams[2]) && dxball_crt_isatty(descriptor)))
            dxball_crt_get_buffer(stream);
    }
    if (stream->flags & 0x108) {
        expected = (int)(stream->cursor - stream->buffer);
        stream->cursor = stream->buffer + 1;
        stream->count = stream->capacity - 1;
        if (expected > 0) written = dxball_crt_write(descriptor, stream->buffer, expected);
        else {
            DxBallLowioRecord *record = descriptor != -1
                ? &__pioinfo[descriptor >> 5][descriptor & 31] : &dxball_crt_invalid_io;
            if (record->flags & 0x20) dxball_crt_seek(descriptor, 0, 2);
        }
        *stream->buffer = (char)value;
    } else {
        expected = 1;
        written = dxball_crt_write(descriptor, &value, 1);
    }
    if (written != expected) {
        stream->flags |= 0x20;
        return -1;
    }
    return value & 0xff;
}

/* FUNCTION: DXBALL 0x00417AA0 */
unsigned int dxball_crt_fread(void *buffer, unsigned int element_size,
                            unsigned int elements, DxBallCrtStream *stream)
{
    struct {
        char *destination;
        unsigned int total;
        unsigned int capacity;
    } transfer;
    unsigned int remaining;
    transfer.destination = (char *)buffer;
    transfer.total = element_size * elements;
    remaining = transfer.total;
    if (transfer.total == 0) return 0;
    transfer.capacity = stream->flags & 0x10c ? (unsigned int)stream->capacity : 4096;
    while (remaining != 0) {
        if ((stream->flags & 0x10c) && stream->count != 0) {
            unsigned int available = (unsigned int)stream->count;
            unsigned int amount = remaining < available ? remaining : available;
            remaining -= amount;
            memcpy(transfer.destination, stream->cursor, amount);
            stream->count -= amount;
            stream->cursor += amount;
            transfer.destination += amount;
        } else if (remaining >= transfer.capacity) {
            unsigned int amount = transfer.capacity ? remaining - remaining % transfer.capacity : remaining;
            int received = dxball_crt_read(stream->descriptor, transfer.destination, amount);
            if (received == 0) {
                stream->flags |= 0x10;
                return (transfer.total - remaining) / element_size;
            }
            if (received == -1) {
                stream->flags |= 0x20;
                return (transfer.total - remaining) / element_size;
            }
            remaining -= received;
            transfer.destination += received;
        } else {
            int value = dxball_crt_fill_input(stream);
            if (value == -1) return (transfer.total - remaining) / element_size;
            --remaining;
            *transfer.destination++ = (char)value;
            transfer.capacity = (unsigned int)stream->capacity;
        }
    }
    return elements;
}
