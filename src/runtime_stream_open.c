#include "runtime_stream_open.h"
#include <stdarg.h>

#define DXBALL_CRT_OPEN_RECORD(block, offset) \
    ((DxBallLowioRecord *)((char *)*(block) + (offset)))

/* FUNCTION: DXBALL 0x00417BF0 */
DxBallCrtStream *dxball_crt_fsopen(const char *filename, const char *mode, int sharing)
{
    DxBallCrtStream *stream = dxball_crt_get_stream();
    if (stream == NULL) return NULL;
    return dxball_crt_open_file(filename, mode, sharing, stream);
}

/* FUNCTION: DXBALL 0x00417C20 */
DxBallCrtStream *dxball_crt_fopen(const char *filename, const char *mode)
{
    return dxball_crt_fsopen(filename, mode, 0x40);
}

/* FUNCTION: DXBALL 0x0041A390 */
DxBallCrtStream *dxball_crt_open_file(const char *filename, const char *mode,
                                   int sharing, DxBallCrtStream *stream)
{
    int access_hint = 0;
    int commit_hint = 0;
    int active;
    int open_flags;
    int stream_flags;
    int descriptor;
    switch (*mode) {
    case 'a': open_flags = 0x109; goto writing;
    case 'r': open_flags = 0; stream_flags = dxball_crt_default_commit | 1; break;
    case 'w': open_flags = 0x301;
writing:
        stream_flags = dxball_crt_default_commit | 2;
        break;
    default: return NULL;
    }
    active = 1;
    ++mode;
    while (*mode != '\0' && active) {
        switch (*mode) {
        case '+':
            if (open_flags & 2) active = 0;
            else {
                open_flags |= 2;
                stream_flags |= 0x80;
                open_flags &= ~1;
                stream_flags &= ~3;
            }
            break;
        case 'D':
            if (open_flags & 0x40) active = 0;
            else open_flags |= 0x40;
            break;
        case 'R':
            if (access_hint) active = 0;
            else { access_hint = 1; open_flags |= 0x10; }
            break;
        case 'S':
            if (access_hint) active = 0;
            else { access_hint = 1; open_flags |= 0x20; }
            break;
        case 'T':
            if (open_flags & 0x1000) active = 0;
            else open_flags |= 0x1000;
            break;
        case 'b':
            if (open_flags & 0xc000) active = 0;
            else open_flags |= 0x8000;
            break;
        case 'c':
            if (commit_hint) active = 0;
            else { commit_hint = 1; stream_flags |= 0x4000; }
            break;
        case 'n':
            if (commit_hint) active = 0;
            else { commit_hint = 1; stream_flags &= ~0x4000; }
            break;
        case 't':
            if (open_flags & 0xc000) active = 0;
            else open_flags |= 0x4000;
            break;
        default: active = 0;
        }
        ++mode;
    }
    descriptor = dxball_crt_sopen(filename, open_flags, sharing, 0x1a4);
    if (descriptor < 0) return NULL;
    ++dxball_crt_buffer_requests;
    stream->flags = stream_flags;
    stream->count = 0;
    stream->cursor = NULL;
    stream->buffer = NULL;
    stream->temporary_name = NULL;
    stream->descriptor = descriptor;
    return stream;
}

/* FUNCTION: DXBALL 0x0041D7D0 */
int dxball_crt_allocate_descriptor(void)
{
    int descriptor = -1;
    int index = 0;
    int base = 0;
    DxBallLowioRecord **slot;
    for (slot = __pioinfo; slot < __pioinfo + 64; ++slot, ++index, base += 32) {
        DxBallLowioRecord *record = *slot;
        if (record != NULL) {
            DxBallLowioRecord *end = record + 32;
            for (; record < end; ++record) {
                if ((record->flags & 1) == 0) {
                    record->handle = (void *)(size_t)-1;
                    descriptor = (int)(record - *slot) + base;
                    break;
                }
            }
            if (descriptor != -1) break;
        } else {
            record = (DxBallLowioRecord *)dxball_runtime_malloc(32 * sizeof(*record));
            if (record != NULL) {
                _nhandle += 32;
                __pioinfo[index] = record;
                for (; record < __pioinfo[index] + 32; ++record) {
                    record->flags = 0;
                    record->handle = (void *)(size_t)-1;
                    record->lookahead = '\n';
                }
                descriptor = index << 5;
            }
            break;
        }
    }
    return descriptor;
}

/* FUNCTION: DXBALL 0x0041DB80 */
int dxball_crt_sopen(const char *filename, int flags, int sharing, ...)
{
    struct {
        union { DxBallCrtDword sharing; unsigned char device_flags; } share;
        union { DxBallCrtDword access; size_t record_offset; } access;
        DxBallCrtDword disposition;
        DxBallCrtSecurityAttributes security;
    } creation;
    unsigned char io_flags;
    DxBallCrtDword attributes;
    void *handle;
    int descriptor;
    DxBallLowioRecord **block;
    creation.security.descriptor = NULL;
    creation.security.inherit = 0;
    creation.security.length = sizeof(creation.security);
    if ((flags & 0x80) == 0) creation.security.inherit = 1;
    if (flags & 0x8000) io_flags = 0;
    else if (flags & 0x4000) io_flags = 0x80;
    else io_flags = dxball_crt_default_file_mode == 0x8000 ? 0 : 0x80;
    switch (flags & 3) {
    case 0: creation.access.access = 0x80000000UL; break;
    case 1: creation.access.access = 0x40000000UL; break;
    case 2: creation.access.access = 0xc0000000UL; break;
    default: errno = 22; _doserrno = 0; return -1;
    }
    switch (sharing) {
    case 0x10: creation.share.sharing = 0; break;
    case 0x20: creation.share.sharing = 1; break;
    case 0x30: creation.share.sharing = 2; break;
    case 0x40: creation.share.sharing = 3; break;
    default: errno = 22; _doserrno = 0; return -1;
    }
    switch (flags & 0x700) {
    case 0: case 0x400: creation.disposition = 3; break;
    case 0x100: creation.disposition = 4; break;
    case 0x200: case 0x600: creation.disposition = 5; break;
    case 0x300: creation.disposition = 2; break;
    case 0x500: case 0x700: creation.disposition = 1; break;
    default: errno = 22; _doserrno = 0; return -1;
    }
    attributes = 0x80;
    if (flags & 0x100) {
        int mode;
        va_list arguments;
        va_start(arguments, sharing);
        mode = va_arg(arguments, int);
        va_end(arguments);
        if ((~dxball_crt_creation_mask & mode & 0x80) == 0) attributes = 1;
    }
    if (flags & 0x40) {
        creation.access.access |= 0x10000;
        attributes |= 0x04000000;
    }
    if (flags & 0x1000) attributes |= 0x100;
    if (flags & 0x20) attributes |= 0x08000000;
    else if (flags & 0x10) attributes |= 0x10000000;
    descriptor = dxball_crt_allocate_descriptor();
    if (descriptor == -1) { errno = 24; _doserrno = 0; return -1; }
    handle = CreateFileA(filename, creation.access.access, creation.share.sharing,
                         &creation.security, creation.disposition, attributes, NULL);
    if (handle == (void *)(size_t)-1) {
        dxball_crt_map_os_error(GetLastError());
        return -1;
    }
    {
        DxBallCrtDword type = GetFileType(handle);
        if (type == 0) {
            CloseHandle(handle);
            dxball_crt_map_os_error(GetLastError());
            return -1;
        }
        if (type == 2) io_flags |= 0x40;
        else if (type == 3) io_flags |= 8;
    }
    dxball_crt_set_osfhandle(descriptor, (DxBallCrtOsHandle)handle);
    io_flags |= 1;
    block = &__pioinfo[descriptor >> 5];
    {
        DxBallLowioRecord *records = *block;
        creation.access.record_offset = (descriptor & 31) * sizeof(DxBallLowioRecord);
        ((DxBallLowioRecord *)((char *)records + creation.access.record_offset))->flags = io_flags;
    }
    creation.share.device_flags = io_flags & 0x48;
    if (creation.share.device_flags == 0 && (io_flags & 0x80) && (flags & 2)) {
        DxBallCrtLong end = dxball_crt_seek(descriptor, -1, 2);
        if (end == -1) {
            if (_doserrno != 131) { dxball_crt_close(descriptor); return -1; }
        } else {
            char tail = 0;
            if (dxball_crt_read(descriptor, &tail, 1) == 0 && tail == 0x1a &&
                dxball_crt_chsize(descriptor, end) == -1) {
                dxball_crt_close(descriptor);
                return -1;
            }
            if (dxball_crt_seek(descriptor, 0, 0) == -1) {
                dxball_crt_close(descriptor);
                return -1;
            }
        }
    }
    if (creation.share.device_flags == 0 && (flags & 8))
        DXBALL_CRT_OPEN_RECORD(block, creation.access.record_offset)->flags |= 0x20;
    return descriptor;
}
