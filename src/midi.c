#include "allocator.h"
#include "midi.h"
#include <stdlib.h>
#include <string.h>

DxBallMidiApi dxball_midi_api;
DxBallMusic *dxball_music;
enum { MDS_MAGIC = 0x4953444d, MDS_FREED = 0x61746164, MIDI_HEADER_BYTES = 64 };

static DxBallUInt read_word(const DxBallByte *data)
{
    DxBallUInt value;
    memcpy(&value, data, sizeof(value));
    return value;
}
static void write_word(DxBallByte *data, DxBallUInt value)
{ memcpy(data, &value, sizeof(value)); }
static DxBallMidiHeader *next_buffer(DxBallMidiHeader *header)
{ return (DxBallMidiHeader *)((DxBallByte *)header + sizeof(*header) + header->buffer_length); }
static void free_buffers(DxBallMdsContext *context)
{
    DxBallMidiHandle handle;
    handle = dxball_midi_api.global_handle(context->buffers);
    dxball_midi_api.global_unlock(handle);
    handle = dxball_midi_api.global_handle(context->buffers);
    dxball_midi_api.global_free(handle);
}

DxBallInt dxball_expand_mds_events(const DxBallMdsInput *input, DxBallMidiHeader *header)
{
    const DxBallByte *source = input->data;
    DxBallByte *destination = header->data;
    DxBallUInt remaining = input->remaining, capacity = header->buffer_length;
    DxBallUInt event, payload;
    if ((remaining & 3) != 0) return 0;
    while (remaining != 0) {
        if (capacity < 12) return 0;
        write_word(destination, read_word(source));
        if (remaining == 4) return 0;
        write_word(destination + 4, 0);
        event = read_word(source + 4);
        payload = (event & 0x80000000UL) ? event & 0xffffff : 0;
        payload = (payload + 3) & 0xfffffffcUL;
        write_word(destination + 8, event);
        if (payload != 0) {
            if (remaining - 8 < payload || capacity - 12 < payload) return 0;
            memcpy(destination + 12, source + 8, payload);
        }
        destination += 12 + payload; source += 8 + payload;
        capacity -= 12 + payload; remaining -= 8 + payload;
    }
    header->bytes_recorded = (DxBallUInt)(destination - header->data);
    return 1;
}

DxBallInt dxball_parse_mds(DxBallMdsContext *context, const void *memory, DxBallUInt length)
{
    const DxBallByte *data = (const DxBallByte *)memory;
    DxBallUInt chunk, bytes;
    DxBallInt remaining, result = 0;
    DxBallMidiHandle handle;
    DxBallMidiHeader *header;
    DxBallMdsInput input;
    context->buffers = NULL;
    if (length < 12 || read_word(data) != 0x46464952UL || read_word(data + 8) != 0x5344494dUL)
        return 3;
    chunk = read_word(data + 4); data += 12; length -= 12;
    if (length + 4 < chunk) return 3;
    if (length < 8 || read_word(data) != 0x20746d66UL) return 3;
    chunk = read_word(data + 4);
    if (length < chunk || chunk < 12) return 3;
    data += 8; length -= 8;
    context->time_division = read_word(data);
    context->buffer_capacity = read_word(data + 4);
    context->format_flags = read_word(data + 8);
    data += chunk; length -= chunk;
    if (length < 8 || read_word(data) != 0x61746164UL) return 3;
    chunk = read_word(data + 4);
    if (length < chunk || chunk < 4) return 3;
    context->buffer_count = (DxBallInt)read_word(data + 8);
    data += 12; length -= 12;
    handle = dxball_midi_api.global_alloc(0x2002,
        (sizeof(DxBallMidiHeader) + context->buffer_capacity) * (size_t)context->buffer_count);
    context->buffers = (DxBallMidiHeader *)dxball_midi_api.global_lock(handle);
    if (context->buffers == NULL) return 1;
    header = context->buffers;
    for (remaining = context->buffer_count; remaining != 0; --remaining) {
        header->data = (DxBallByte *)header + sizeof(*header);
        header->buffer_length = context->buffer_capacity;
        header->flags = 0; header->user = (size_t)context; header->next = NULL;
        if (length < 8) { result = 3; break; }
        bytes = read_word(data + 4); data += 8;
        if (context->buffer_capacity < bytes || length - 8 < bytes) { result = 3; break; }
        if ((context->format_flags & 1) == 0) {
            header->bytes_recorded = bytes; memcpy(header->data, data, bytes);
        } else {
            input.data = data; input.length = input.remaining = bytes;
            if (!dxball_expand_mds_events(&input, header)) { result = 3; break; }
        }
        length -= 8 + bytes; data += bytes; header = next_buffer(header);
    }
    if (result != 0 && context->buffers != NULL) free_buffers(context);
    return result;
}

DxBallInt dxball_open_mds(DxBallMdsContext **output, const void *input,
                         DxBallUInt length, DxBallByte mode)
{
    DxBallMdsContext *context = NULL;
    DxBallMidiHandle file = (DxBallMidiHandle)-1, mapping = 0;
    const void *view = input;
    DxBallInt result, mapped = 0;
    if ((mode & 3) == 0 || (mode & 3) == 3) result = 4;
    else {
        context = (DxBallMdsContext *)dxball_midi_api.local_alloc(0x40, sizeof(*context));
        if (context == NULL) result = 1;
        else {
            context->magic = MDS_MAGIC; context->stream = 0; context->pending_buffers = 0;
            result = 2;
            if ((mode & 2) == 0) {
                mapped = 1;
                file = dxball_midi_api.create_file((const char *)input,0x80000000UL,1,NULL,3,0x80,0);
                view = NULL;
                if (file == (DxBallMidiHandle)-1) goto done;
                length = dxball_midi_api.file_size(file, NULL);
                mapping = dxball_midi_api.create_mapping(file,NULL,2,0,0,NULL);
                if (mapping == 0) goto done;
                view = dxball_midi_api.map_view(mapping,4,0,0,0);
                if (view == NULL) goto done;
            }
            result = dxball_parse_mds(context, view, length);
        }
    }
done:
    if (result == 0) *output = context;
    else if (context != NULL) dxball_midi_api.local_free(context);
    if (mapped) {
        if (view != NULL) dxball_midi_api.unmap_view(view);
        if (mapping != 0) dxball_midi_api.close_handle(mapping);
        if (file != (DxBallMidiHandle)-1) dxball_midi_api.close_handle(file);
    }
    return result;
}

/* FUNCTION: DXBALL 0x004016E0 */
DxBallInt dxball_release_mds(DxBallMdsContext *context)
{
    DxBallMdsContext *current;
    if (context->magic != MDS_MAGIC) return 6;
    current = context;
    if (current->stream != 0) dxball_stop_mds(context);
    if (current->buffers != NULL) {
        dxball_midi_api.global_unlock(dxball_midi_api.global_handle(current->buffers));
        dxball_midi_api.global_free(dxball_midi_api.global_handle(current->buffers));
    }
    current->magic = MDS_FREED;
    dxball_midi_api.local_free(current);
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
        if (dxball_midi_api.stream_open(&current->stream, &device, 1,
                dxball_midi_callback, 0, 0x30000) != 0) {
            result = 5;
            goto done;
        }
        property.size = 8;
        property.value = current->time_division;
        if (dxball_midi_api.stream_property(current->stream, &property,
                0x80000001UL) != 0) {
            result = 5;
            goto done;
        }
        header = current->buffers;
        for (remaining = current->buffer_count; remaining != 0; --remaining) {
            if (dxball_midi_api.prepare_header(current->stream, header, MIDI_HEADER_BYTES) != 0 ||
                dxball_midi_api.stream_out(current->stream, header, MIDI_HEADER_BYTES) != 0) {
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
    if (dxball_midi_api.stream_restart(current->stream) != 0) result = 5;
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
    if (dxball_midi_api.stream_pause(current->stream) != 0) return 5;
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
    if (dxball_midi_api.out_reset(current->stream) != 0) {
        current->state &= ~1UL;
        return 5;
    }
    header = current->buffers;
    for (remaining = current->buffer_count; remaining != 0; --remaining) {
        dxball_midi_api.unprepare_header(current->stream, header, MIDI_HEADER_BYTES);
        header = (DxBallMidiHeader *)((DxBallByte *)header +
            (sizeof(*header) + header->buffer_length));
    }
    dxball_midi_api.stream_close(current->stream);
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
        dxball_midi_api.stream_out(context->stream, current_header, MIDI_HEADER_BYTES) == 0)
        return;
    --context->pending_buffers;
    return;
}

/* FUNCTION: DXBALL 0x00401B90 */
DxBallInt dxball_load_music(const char *path, DxBallInt play)
{
    if (dxball_music != NULL) dxball_close_music();
    dxball_music = (DxBallMusic *)dxball_runtime_new(sizeof(*dxball_music));
    if (dxball_open_mds(&dxball_music->context, path, 0, 1) != 0) {
        dxball_runtime_delete(dxball_music);
        dxball_music = NULL;
        return 0;
    }
    dxball_music->playing = 0;
    if (play != 0) {
        if (dxball_play_mds(dxball_music->context, 1) != 0) {
            dxball_release_mds(dxball_music->context);
            dxball_runtime_delete(dxball_music);
            dxball_music = NULL;
            return 0;
        }
        dxball_music->playing = 1;
    }
    return 1;
}

/* FUNCTION: DXBALL 0x00401C90 */
void dxball_resume_music(void)
{
    if (dxball_music == NULL) return;
    if (dxball_play_mds(dxball_music->context, 1) != 0) return;
    dxball_music->playing = 1;
    return;
}

/* FUNCTION: DXBALL 0x00401CE0 */
void dxball_pause_music(void)
{
    if (dxball_music == NULL) return;
    if (dxball_pause_mds(dxball_music->context) != 0) return;
    dxball_music->playing = 0;
    return;
}

/* FUNCTION: DXBALL 0x00401D30 */
void dxball_restart_music(void)
{
    if (dxball_music == NULL) return;
    if (dxball_stop_mds(dxball_music->context) != 0) return;
    if (dxball_play_mds(dxball_music->context, 1) != 0) return;
    dxball_music->playing = 1;
    return;
}

/* FUNCTION: DXBALL 0x00401DA0 */
void dxball_close_music(void)
{
    if (dxball_music == NULL) return;
    dxball_stop_mds(dxball_music->context);
    dxball_release_mds(dxball_music->context);
    dxball_runtime_delete(dxball_music);
    dxball_music = NULL;
    return;
}
