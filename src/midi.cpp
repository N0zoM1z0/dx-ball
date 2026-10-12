#include <stdlib.h>
#include <string.h>

extern "C" {
#include "allocator.h"
#include "midi.h"
#include "file.h"
#include "memory.h"
}

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

    if ((mode & 3) == 0 || (mode & 3) == 3) {
        result = 4;
        goto done;
    }
    context = (DxBallMdsContext *)dxball_local_alloc(0x40, sizeof(*context));
    if (context == NULL) {
        result = 1;
        goto done;
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
            goto done;
        }
        length = dxball_file_size(file, NULL);
        mapping = dxball_midi_create_mapping(file, NULL, 2, 0, 0, NULL);
        if (mapping == 0) {
            result = 2;
            goto done;
        }
        input = dxball_midi_map_view(mapping, 4, 0, 0, 0);
        if (input == NULL) {
            result = 2;
            goto done;
        }
    }
    result = dxball_parse_mds(context, input, length);

done:
    if (result != 0) {
        if (context != NULL) dxball_local_free(context);
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
    {
        DxBallMidiHeader input;
        DxBallUInt chunk;
        {
            struct {
                DxBallMidiHeader *header;
                DxBallInt result, remaining;
            } progress;

            progress.result = 0;
            context->buffers = NULL;
            if (length < 12 || *(const DxBallUInt *)memory != 0x46464952UL ||
                ((const DxBallUInt *)memory)[2] != 0x5344494dUL) {
                progress.result = 3;
                goto done;
            }
            chunk = ((const DxBallUInt *)memory)[1];
            memory = (const DxBallUInt *)memory + 2;
            length -= 8;
            if (chunk > length) {
                progress.result = 3;
                goto done;
            }
            memory = (const DxBallUInt *)memory + 1;
            length -= 4;
            if (length < 8 || *(const DxBallUInt *)memory != 0x20746d66UL ||
                (chunk = ((const DxBallUInt *)memory)[1]) > length || chunk < 12) {
                progress.result = 3;
                goto done;
            }
            memory = (const DxBallUInt *)memory + 2;
            length -= 8;
            context->format = *(const DxBallMdsFormat *)memory;
            memory = (const DxBallByte *)memory + chunk;
            length -= chunk;
            if (length < 8 || *(const DxBallUInt *)memory != 0x61746164UL ||
                (chunk = ((const DxBallUInt *)memory)[1]) > length || chunk < 4) {
                progress.result = 3;
                goto done;
            }
            context->buffer_count = (DxBallInt)((const DxBallUInt *)memory)[2];
            memory = (const DxBallUInt *)memory + 3;
            length -= 12;
            chunk = (DxBallUInt)((context->format.buffer_capacity + sizeof(*progress.header)) *
                context->buffer_count);
            context->buffers = (DxBallMidiHeader *)dxball_midi_global_lock(
                dxball_midi_global_alloc(0x2002, chunk));
            if (context->buffers == NULL) {
                progress.result = 1;
                goto done;
            }
            progress.header = context->buffers;
            for (progress.remaining = context->buffer_count; progress.remaining != 0; --progress.remaining) {
                progress.header->data = (DxBallByte *)(progress.header + 1);
                progress.header->buffer_length = context->format.buffer_capacity;
                progress.header->flags = 0;
                progress.header->user = (size_t)context;
                progress.header->next = NULL;
                if (length < 8) {
                    progress.result = 3;
                    goto done;
                }
                block = *(const DxBallMdsBlock *)memory;
                length -= sizeof(block);
                memory = (const DxBallByte *)memory + sizeof(block);
                if (context->format.buffer_capacity < block.bytes || block.bytes > length) {
                    progress.result = 3;
                    goto done;
                }
                if ((context->format.flags & 1) == 0) {
                    progress.header->bytes_recorded = block.bytes;
                    memcpy(progress.header->data, memory, block.bytes);
                } else {
                    input.data = (DxBallByte *)memory;
                    input.buffer_length = input.bytes_recorded = block.bytes;
                    if (!dxball_expand_mds_events(&input, progress.header)) {
                        progress.result = 3;
                        goto done;
                    }
                }
                length -= block.bytes;
                memory = (const DxBallByte *)memory + block.bytes;
                progress.header = (DxBallMidiHeader *)((DxBallByte *)progress.header +
                    (context->format.buffer_capacity + sizeof(*progress.header)));
            }
        done:
            if (progress.result != 0 && context->buffers != NULL) {
                dxball_midi_global_unlock(dxball_midi_global_handle(context->buffers));
                dxball_midi_global_free(dxball_midi_global_handle(context->buffers));
            }
            return progress.result;
        }
    }
}

/* FUNCTION: DXBALL 0x00401580 */
DxBallInt dxball_expand_mds_events(const DxBallMidiHeader *input,
                                  DxBallMidiHeader *header)
{
    DxBallUInt payload;
    {
        struct {
            DxBallUInt remaining, capacity;
            DxBallUInt *destination;
            const DxBallUInt *source;
        } cursor;
        cursor.source = (const DxBallUInt *)input->data;
        cursor.destination = (DxBallUInt *)header->data;
        cursor.remaining = input->bytes_recorded;
        cursor.capacity = header->buffer_length;

        if ((cursor.remaining & 3) != 0) return 0;
        while (cursor.remaining != 0) {
            if (cursor.capacity < 12) return 0;
            *cursor.destination++ = *cursor.source++;
            cursor.remaining -= 4;
            if (cursor.remaining == 0) return 0;
            *cursor.destination++ = 0;
            cursor.capacity -= 8;
            payload = 0;
            if ((*cursor.source & 0x80000000UL) != 0)
                payload = *cursor.source & 0xffffffUL;
            payload = (payload + 3) & 0xfffffffcUL;
            *cursor.destination++ = *cursor.source++;
            cursor.remaining -= 4;
            cursor.capacity -= 4;
            if (payload != 0) {
                if (cursor.remaining < payload || cursor.capacity < payload) return 0;
                memcpy(cursor.destination, cursor.source, payload);
            }
            cursor.destination += payload / sizeof(*cursor.destination);
            cursor.source += payload / sizeof(*cursor.source);
            cursor.remaining -= payload;
            cursor.capacity -= payload;
        }
        header->bytes_recorded = (DxBallUInt)((DxBallByte *)cursor.destination - header->data);
        return 1;
    }
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
    dxball_local_free(current);
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
    if (dxball_midi_stream_restart(current->stream) != 0) {
        result = 5;
        goto done;
    }
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
    if (context->magic != MDS_MAGIC) return 6;
    {
        DxBallMdsContext *current;
        DxBallMidiHeader *header;
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
    }
    return 0;
}

/* FUNCTION: DXBALL 0x00401B10 */
void DXBALL_DDCALL dxball_midi_callback(DxBallMidiHandle stream, DxBallUInt message,
    size_t instance, DxBallMidiHeader *header, size_t unused)
{
    DxBallMdsContext *context;
    (void)stream; (void)instance; (void)unused;
    {
        DxBallMidiHeader *current_header;
        current_header = header;
        if (message != 0x3c9) return;
        context = (DxBallMdsContext *)current_header->user;
        /* Two consecutive reads/stores are present in the original instruction
           dossier. Their original source spelling remains unresolved. */
        context = (DxBallMdsContext *)current_header->user;
        if ((context->state & 2) != 0 && (context->state & 1) == 0 &&
            dxball_midi_stream_out(context->stream, current_header, MIDI_HEADER_BYTES) == 0)
            return;
    }
    --context->pending_buffers;
    return;
}
