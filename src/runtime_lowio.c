#include "runtime_lowio.h"

#define DXBALL_CRT_IO_RECORD(block, byte_offset) \
    ((DxBallLowioRecord *)((char *)*(block) + (byte_offset)))

typedef struct DxBallCrtErrorMap {
    DxBallCrtDword os_error;
    int error;
} DxBallCrtErrorMap;

/* Complete original 45-record initialized OS-error table at 0x004234D8. */
static DxBallCrtErrorMap dxball_crt_error_map[45] = {
    { 1U, 22 },
    { 2U, 2 },
    { 3U, 2 },
    { 4U, 24 },
    { 5U, 13 },
    { 6U, 9 },
    { 7U, 12 },
    { 8U, 12 },
    { 9U, 12 },
    { 10U, 7 },
    { 11U, 8 },
    { 12U, 22 },
    { 13U, 22 },
    { 15U, 2 },
    { 16U, 13 },
    { 17U, 18 },
    { 18U, 2 },
    { 33U, 13 },
    { 53U, 2 },
    { 65U, 13 },
    { 67U, 2 },
    { 80U, 17 },
    { 82U, 13 },
    { 83U, 13 },
    { 87U, 22 },
    { 89U, 11 },
    { 108U, 13 },
    { 109U, 32 },
    { 112U, 28 },
    { 114U, 9 },
    { 6U, 22 },
    { 128U, 10 },
    { 129U, 10 },
    { 130U, 9 },
    { 131U, 22 },
    { 132U, 13 },
    { 145U, 41 },
    { 158U, 13 },
    { 161U, 2 },
    { 164U, 11 },
    { 167U, 13 },
    { 183U, 17 },
    { 206U, 2 },
    { 215U, 11 },
    { 1816U, 12 },
};

/* FUNCTION: DXBALL 0x0041D9D0 */
DxBallCrtOsHandle dxball_crt_get_osfhandle(int descriptor)
{
    if ((unsigned int)descriptor < (unsigned int)_nhandle &&
        (__pioinfo[descriptor >> 5][descriptor & 31].flags & 1)) {
        return (DxBallCrtOsHandle)__pioinfo[descriptor >> 5][descriptor & 31].handle;
    }
    errno = 9;
    _doserrno = 0;
    return -1;
}

/* FUNCTION: DXBALL 0x0041DA20 */
int dxball_crt_commit(int descriptor)
{
    DxBallCrtDword error;
    if ((unsigned int)descriptor < (unsigned int)_nhandle &&
        (__pioinfo[descriptor >> 5][descriptor & 31].flags & 1)) {
        error = FlushFileBuffers((void *)dxball_crt_get_osfhandle(descriptor)) ? 0 : GetLastError();
        if (error != 0) {
            errno = 9;
            _doserrno = error;
            return -1;
        }
        return (int)error;
    }
    errno = 9;
    return -1;
}

/* FUNCTION: DXBALL 0x0041AF40 */
DxBallCrtLong dxball_crt_seek(int descriptor, DxBallCrtLong offset, int origin)
{
    DxBallLowioRecord **block;
    size_t record_offset;
    void *handle;
    DxBallCrtDword position, error;
    if ((unsigned int)descriptor >= (unsigned int)_nhandle) goto bad_descriptor;
    block = &__pioinfo[descriptor >> 5];
    record_offset = (descriptor & 31) * sizeof(DxBallLowioRecord);
    if ((DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 1) == 0) goto bad_descriptor;
    handle = (void *)dxball_crt_get_osfhandle(descriptor);
    if (handle == (void *)(size_t)-1) {
        errno = 9;
        return -1;
    }
    position = SetFilePointer(handle, offset, NULL, (DxBallCrtDword)origin);
    error = position == (DxBallCrtDword)-1 ? GetLastError() : 0;
    if (error != 0) {
        dxball_crt_map_os_error(error);
        return -1;
    }
    DXBALL_CRT_IO_RECORD(block, record_offset)->flags &= 0xfd;
    return (DxBallCrtLong)position;
bad_descriptor:
    errno = 9;
    _doserrno = 0;
    return -1;
}

/* FUNCTION: DXBALL 0x0041A770 */
int dxball_crt_write(int descriptor, const void *buffer, unsigned int bytes)
{
    struct {
        DxBallLowioRecord **block;
        size_t record_offset;
        DxBallCrtDword total;
    } progress;
    struct {
        DxBallCrtDword error;
        DxBallCrtDword written;
    } outcome;
    unsigned int inserted;
    /* A final LF can cross the 1024-byte threshold by one generated CR. */
    char translated[1025];
    if ((unsigned int)descriptor >= (unsigned int)_nhandle) goto bad_descriptor;
    progress.block = &__pioinfo[descriptor >> 5];
    progress.record_offset = (descriptor & 31) * sizeof(DxBallLowioRecord);
    if ((DXBALL_CRT_IO_RECORD(progress.block, progress.record_offset)->flags & 1) == 0)
        goto bad_descriptor;
    inserted = 0;
    progress.total = 0;
    if (bytes == 0) return 0;
    if (DXBALL_CRT_IO_RECORD(progress.block, progress.record_offset)->flags & 0x20)
        dxball_crt_seek(descriptor, 0, 2);
    if (DXBALL_CRT_IO_RECORD(progress.block, progress.record_offset)->flags & 0x80) {
        const char *input;
        outcome.error = 0;
        input = (const char *)buffer;
        while ((unsigned int)(input - (const char *)buffer) < bytes) {
            char *output;
            output = translated;
            do {
                char value;
                if ((unsigned int)(input - (const char *)buffer) >= bytes) break;
                value = *input++;
                if (value == '\n') {
                    *output = '\r';
                    ++inserted;
                    ++output;
                }
                *output++ = value;
            } while (output - translated < 1024);
            if (!WriteFile(DXBALL_CRT_IO_RECORD(progress.block, progress.record_offset)->handle,
                           translated, (DxBallCrtDword)(output - translated), &outcome.written, NULL))
                goto os_write_error;
            progress.total += outcome.written;
            if ((int)outcome.written < (int)(output - translated)) break;
        }
    } else {
        if (!WriteFile(DXBALL_CRT_IO_RECORD(progress.block, progress.record_offset)->handle,
                       buffer, bytes, &outcome.written, NULL)) goto os_write_error;
        outcome.error = 0;
        progress.total = outcome.written;
    }
    goto write_result;
os_write_error:
    outcome.error = GetLastError();
write_result:
    if (progress.total == 0) {
        if (outcome.error != 0) {
            if (outcome.error == 5) {
                errno = 9;
                _doserrno = outcome.error;
            } else {
                dxball_crt_map_os_error(outcome.error);
            }
            return -1;
        }
        if ((DXBALL_CRT_IO_RECORD(progress.block, progress.record_offset)->flags & 0x40) &&
            *(const char *)buffer == 0x1a) return 0;
        errno = 28;
        _doserrno = 0;
        return -1;
    }
    return (int)(progress.total - inserted);
bad_descriptor:
    errno = 9;
    _doserrno = 0;
    return -1;
}

/* FUNCTION: DXBALL 0x0041A9A0 */
void dxball_crt_map_os_error(DxBallCrtDword error)
{
    unsigned int index;
    DxBallCrtErrorMap *entry;
    _doserrno = error;
    index = 0;
    entry = dxball_crt_error_map;
    do {
        if (entry->os_error == error) {
            errno = dxball_crt_error_map[index].error;
            return;
        }
        ++entry;
        ++index;
    } while (entry < dxball_crt_error_map + 45);
    if (error >= 19 && error <= 36) errno = 13;
    else if (error >= 188 && error <= 202) errno = 8;
    else errno = 22;
}
