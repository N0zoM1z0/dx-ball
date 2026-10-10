#include "allocator.h"
#include "midi.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>

void *(DXBALL_DDCALL *dxball_midi_local_alloc)(DxBallUInt, size_t);
void *(DXBALL_DDCALL *dxball_midi_local_free)(void *);
DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_create_mapping)(DxBallMidiHandle,
        void *, DxBallUInt, DxBallUInt, DxBallUInt, const char *);
void *(DXBALL_DDCALL *dxball_midi_map_view)(DxBallMidiHandle, DxBallUInt,
        DxBallUInt, DxBallUInt, size_t);
DxBallInt (DXBALL_DDCALL *dxball_midi_unmap_view)(const void *);
DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_global_alloc)(DxBallUInt, size_t);
void *(DXBALL_DDCALL *dxball_midi_global_lock)(DxBallMidiHandle);
DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_global_handle)(const void *);
DxBallInt (DXBALL_DDCALL *dxball_midi_global_unlock)(DxBallMidiHandle);
DxBallMidiHandle (DXBALL_DDCALL *dxball_midi_global_free)(DxBallMidiHandle);
DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_open)(DxBallMidiHandle *, DxBallUInt *,
        DxBallUInt, DxBallMidiCallback, size_t, DxBallUInt);
DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_property)(DxBallMidiHandle,
        DxBallMidiProperty *, DxBallUInt);
DxBallUInt (DXBALL_DDCALL *dxball_midi_prepare_header)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_out)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_restart)(DxBallMidiHandle);
DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_pause)(DxBallMidiHandle);
DxBallUInt (DXBALL_DDCALL *dxball_midi_out_reset)(DxBallMidiHandle);
DxBallUInt (DXBALL_DDCALL *dxball_midi_unprepare_header)(DxBallMidiHandle,
        DxBallMidiHeader *, DxBallUInt);
DxBallUInt (DXBALL_DDCALL *dxball_midi_stream_close)(DxBallMidiHandle);
enum { MDS_MAGIC = 0x4953444d, MDS_FREED = 0x61746164, MIDI_HEADER_BYTES = 64 };

typedef struct DxBallMdsBlock {
    DxBallUInt start_tick, bytes;
} DxBallMdsBlock;

/* FUNCTION: DXBALL 0x00401000 */
DxBallInt dxball_open_mds(DxBallMdsContext **output, const void *input,
                         DxBallUInt length, DxBallByte mode)
{
    DxBallInt result = 0;
    DxBallMdsContext *context = NULL;
    DxBallInt mapped = 0;
    DxBallMidiHandle file = (DxBallMidiHandle)-1, mapping = 0;

    do {
        if ((mode & 3) == 0 || (mode & 3) == 3) {
            result = 4;
            break;
        }
        context = (DxBallMdsContext *)dxball_midi_local_alloc(0x40, sizeof(*context));
        if (context == NULL) {
            result = 1;
            break;
        }
        context->magic = 0x4953444dUL;
        context->stream = 0;
        context->pending_buffers = 0;
        if ((mode & 2) == 0) {
            mapped = 1;
            file = dxball_file_create((const char *)input, 0x80000000UL,
                                          1, NULL, 3, 0x80, 0);
            input = NULL;
            if (file == (DxBallMidiHandle)-1) {
                result = 2;
                break;
            }
            length = dxball_file_size(file, NULL);
            mapping = dxball_midi_create_mapping(file, NULL, 2, 0, 0, NULL);
            if (mapping == 0) {
                result = 2;
                break;
            }
            input = dxball_midi_map_view(mapping, 4, 0, 0, 0);
            if (input == NULL) {
                result = 2;
                break;
            }
        }
        result = dxball_parse_mds(context, input, length);
    } while (0);

    if (result != 0) {
        if (context != NULL) dxball_midi_local_free(context);
    } else {
        *output = context;
    }
    if (mapped) {
        if (input != NULL) dxball_midi_unmap_view(input);
        if (mapping != 0) dxball_file_close(mapping);
        if (file != (DxBallMidiHandle)-1) dxball_file_close(file);
    }
    return result;
}

/* FUNCTION: DXBALL 0x00401210 */
DxBallInt dxball_parse_mds(DxBallMdsContext *context, const void *memory,
                         DxBallUInt length)
{
    DxBallMdsBlock block;
    DxBallMidiHeader input;
    DxBallUInt chunk;
    DxBallInt remaining, result;
    DxBallMidiHeader *header;

    result = 0;
    context->buffers = NULL;
    if (length < 12 || *(const DxBallUInt *)memory != 0x46464952UL ||
        ((const DxBallUInt *)memory)[2] != 0x5344494dUL) {
        result = 3;
        goto done;
    }
    chunk = ((const DxBallUInt *)memory)[1];
    memory = (const DxBallUInt *)memory + 2;
    length -= 8;
    if (chunk > length) {
        result = 3;
        goto done;
    }
    memory = (const DxBallUInt *)memory + 1;
    length -= 4;
    if (length < 8 || *(const DxBallUInt *)memory != 0x20746d66UL ||
        (chunk = ((const DxBallUInt *)memory)[1]) > length || chunk < 12) {
        result = 3;
        goto done;
    }
    memory = (const DxBallUInt *)memory + 2;
    length -= 8;
    context->format = *(const DxBallMdsFormat *)memory;
    memory = (const DxBallByte *)memory + chunk;
    length -= chunk;
    if (length < 8 || *(const DxBallUInt *)memory != 0x61746164UL ||
        (chunk = ((const DxBallUInt *)memory)[1]) > length || chunk < 4) {
        result = 3;
        goto done;
    }
    context->buffer_count = (DxBallInt)((const DxBallUInt *)memory)[2];
    memory = (const DxBallUInt *)memory + 3;
    length -= 12;
    chunk = (DxBallUInt)((context->format.buffer_capacity + sizeof(*header)) *
        context->buffer_count);
    context->buffers = (DxBallMidiHeader *)dxball_midi_global_lock(
        dxball_midi_global_alloc(0x2002, chunk));
    if (context->buffers == NULL) {
        result = 1;
        goto done;
    }
    header = context->buffers;
    for (remaining = context->buffer_count; remaining != 0; --remaining) {
        header->data = (DxBallByte *)(header + 1);
        header->buffer_length = context->format.buffer_capacity;
        header->flags = 0;
        header->user = (size_t)context;
        header->next = NULL;
        if (length < 8) {
            result = 3;
            break;
        }
        block = *(const DxBallMdsBlock *)memory;
        length -= sizeof(block);
        memory = (const DxBallByte *)memory + sizeof(block);
        if (context->format.buffer_capacity < block.bytes || block.bytes > length) {
            result = 3;
            break;
        }
        if ((context->format.flags & 1) == 0) {
            header->bytes_recorded = block.bytes;
            memcpy(header->data, memory, block.bytes);
        } else {
            input.data = (DxBallByte *)memory;
            input.buffer_length = input.bytes_recorded = block.bytes;
            if (!dxball_expand_mds_events(&input, header)) {
                result = 3;
                break;
            }
        }
        length -= block.bytes;
        memory = (const DxBallByte *)memory + block.bytes;
        header = (DxBallMidiHeader *)((DxBallByte *)header +
            (context->format.buffer_capacity + sizeof(*header)));
    }
done:
    if (result != 0 && context->buffers != NULL) {
        dxball_midi_global_unlock(dxball_midi_global_handle(context->buffers));
        dxball_midi_global_free(dxball_midi_global_handle(context->buffers));
    }
    return result;
}

/* FUNCTION: DXBALL 0x00401580 */
DxBallInt dxball_expand_mds_events(const DxBallMidiHeader *input,
                                  DxBallMidiHeader *header)
{
    DxBallUInt payload;
    const DxBallUInt *source = (const DxBallUInt *)input->data;
    DxBallUInt *destination = (DxBallUInt *)header->data;
    DxBallUInt remaining = input->bytes_recorded;
    DxBallUInt capacity = header->buffer_length;

    if ((remaining & 3) != 0) return 0;
    while (remaining != 0) {
        if (capacity < 12) return 0;
        *destination++ = *source++;
        remaining -= 4;
        if (remaining == 0) return 0;
        *destination++ = 0;
        capacity -= 8;
        payload = 0;
        if ((*source & 0x80000000UL) != 0)
            payload = *source & 0xffffffUL;
        payload = (payload + 3) & 0xfffffffcUL;
        *destination++ = *source++;
        remaining -= 4;
        capacity -= 4;
        if (payload != 0) {
            if (remaining < payload || capacity < payload) return 0;
            memcpy(destination, source, payload);
        }
        destination += payload / sizeof(*destination);
        source += payload / sizeof(*source);
        remaining -= payload;
        capacity -= payload;
    }
    header->bytes_recorded = (DxBallUInt)((DxBallByte *)destination - header->data);
    return 1;
}

/* FUNCTION: DXBALL 0x004016E0 */
DxBallInt dxball_release_mds(DxBallMdsContext *context)
{
    DxBallMdsContext *current;
    if (context->magic != MDS_MAGIC) return 6;
    current = context;
    if (current->stream != 0) dxball_stop_mds(context);
    if (current->buffers != NULL) {
        dxball_midi_global_unlock(dxball_midi_global_handle(current->buffers));
        dxball_midi_global_free(dxball_midi_global_handle(current->buffers));
    }
    current->magic = MDS_FREED;
    dxball_midi_local_free(current);
    return 0;
}

/* FUNCTION: DXBALL 0x00401780 */
DxBallInt dxball_play_mds(DxBallMdsContext *context, DxBallByte flags)
{
    DxBallUInt device;
    DxBallMidiProperty property;
    DxBallInt created, remaining;
    DxBallMdsContext *current;
    DxBallInt result;
    DxBallMidiHeader *header;

    result = 0;
    created = 0;
    if (context->magic != MDS_MAGIC) return 6;
    current = context;
    if (current->stream != 0 && (current->state & 4) == 0) return 7;
    if (current->stream == 0) {
        created = 1;
        device = 0xffffffffUL;
        if (dxball_midi_stream_open(&current->stream, &device, 1,
                dxball_midi_callback, 0, 0x30000) != 0) {
            result = 5;
            goto done;
        }
        property.size = 8;
        property.value = current->format.time_division;
        if (dxball_midi_stream_property(current->stream, &property,
                0x80000001UL) != 0) {
            result = 5;
            goto done;
        }
        header = current->buffers;
        for (remaining = current->buffer_count; remaining != 0; --remaining) {
            if (dxball_midi_prepare_header(current->stream, header, MIDI_HEADER_BYTES) != 0 ||
                dxball_midi_stream_out(current->stream, header, MIDI_HEADER_BYTES) != 0) {
                result = 5;
                goto done;
            }
            ++current->pending_buffers;
            header = (DxBallMidiHeader *)((DxBallByte *)header +
                (sizeof(*header) + header->buffer_length));
        }
    }
    current->state &= ~2UL;
    if ((flags & 1) != 0) current->state |= 2;
    current->state &= ~4UL;
    if (dxball_midi_stream_restart(current->stream) != 0) result = 5;
done:
    if (result != 0 && created != 0 && current->stream != 0)
        dxball_stop_mds(context);
    return result;
}

/* FUNCTION: DXBALL 0x00401990 */
DxBallInt dxball_pause_mds(DxBallMdsContext *context)
{
    DxBallMdsContext *current;
    if (context->magic != MDS_MAGIC) return 6;
    current = context;
    if (current->stream == 0) return 7;
    if ((current->state & 4) != 0) return 0;
    if (dxball_midi_stream_pause(current->stream) != 0) return 5;
    current->state |= 4;
    return 0;
}

/* FUNCTION: DXBALL 0x00401A20 */
DxBallInt dxball_stop_mds(DxBallMdsContext *context)
{
    DxBallInt remaining;
    DxBallMdsContext *current;
    DxBallMidiHeader *header;
    if (context->magic != MDS_MAGIC) return 6;
    current = context;
    if (current->stream == 0) return 7;
    current->state |= 1;
    if (dxball_midi_out_reset(current->stream) != 0) {
        current->state &= ~1UL;
        return 5;
    }
    header = current->buffers;
    for (remaining = current->buffer_count; remaining != 0; --remaining) {
        dxball_midi_unprepare_header(current->stream, header, MIDI_HEADER_BYTES);
        header = (DxBallMidiHeader *)((DxBallByte *)header +
            (sizeof(*header) + header->buffer_length));
    }
    dxball_midi_stream_close(current->stream);
    current->stream = 0;
    current->state = 0;
    return 0;
}

/* FUNCTION: DXBALL 0x00401B10 */
void DXBALL_DDCALL dxball_midi_callback(DxBallMidiHandle stream, DxBallUInt message,
    size_t instance, DxBallMidiHeader *header, size_t unused)
{
    DxBallMdsContext *context;
    DxBallMidiHeader *current_header;
    (void)stream; (void)instance; (void)unused;
    current_header = header;
    if (message != 0x3c9) return;
    context = (DxBallMdsContext *)current_header->user;
    /* Two consecutive reads/stores are present in the original instruction
       dossier. Their original source spelling remains unresolved. */
    context = (DxBallMdsContext *)current_header->user;
    if ((context->state & 2) != 0 && (context->state & 1) == 0 &&
        dxball_midi_stream_out(context->stream, current_header, MIDI_HEADER_BYTES) == 0)
        return;
    --context->pending_buffers;
    return;
}
