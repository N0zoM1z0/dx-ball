#include "runtime_stream_transfer.h"
#include <string.h>

/* FUNCTION: DXBALL 0x00417AA0 */
unsigned int dxball_crt_fread(void *buffer, unsigned int element_size,
                            unsigned int elements, DxBallCrtStream *stream)
{
    char *destination;
    unsigned int total, remaining, capacity, amount, received;
    int value;
    destination = (char *)buffer;
    if ((remaining = total = element_size * elements) == 0) return 0;
    if (stream->flags & 0x10c)
        capacity = (unsigned int)stream->capacity;
    else
        capacity = 4096;
    while (remaining != 0) {
        if ((stream->flags & 0x10c) && stream->count != 0) {
            amount = remaining < (unsigned int)stream->count
                ? remaining : (unsigned int)stream->count;
            memcpy(destination, stream->cursor, amount);
            remaining -= amount;
            stream->count -= amount;
            stream->cursor += amount;
            destination += amount;
        } else if (remaining >= capacity) {
            amount = capacity ? remaining - remaining % capacity : remaining;
            received = (unsigned int)dxball_crt_read(stream->descriptor, destination, amount);
            if (received == 0) {
                stream->flags |= 0x10;
                return (total - remaining) / element_size;
            } else if (received == (unsigned int)-1) {
                stream->flags |= 0x20;
                return (total - remaining) / element_size;
            }
            remaining -= received;
            destination += received;
        } else {
            if ((value = dxball_crt_fill_input(stream)) == -1)
                return (total - remaining) / element_size;
            *destination++ = (char)value;
            --remaining;
            capacity = (unsigned int)stream->capacity;
        }
    }
    return elements;
}
