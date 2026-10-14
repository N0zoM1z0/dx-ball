#include "runtime_lowio_read.h"

#define DXBALL_CRT_IO_RECORD(block, byte_offset) \
    ((DxBallLowioRecord *)((char *)*(block) + (byte_offset)))

/* FUNCTION: DXBALL 0x0041A120 */
int dxball_crt_read(int descriptor, void *buffer, unsigned int bytes)
{
    DxBallLowioRecord **block;
    size_t record_offset;
    struct {
        DxBallCrtDword total;
        DxBallCrtDword read;
        char *end;
    } transfer;
    char next;
    char *input, *output;
    if ((unsigned int)descriptor >= (unsigned int)_nhandle) goto bad_descriptor;
    block = &__pioinfo[descriptor >> 5];
    record_offset = (descriptor & 31) * sizeof(DxBallLowioRecord);
    if ((DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 1) == 0) goto bad_descriptor;
    transfer.total = 0;
    if (bytes == 0 || (DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 2)) return 0;
    input = (char *)buffer;
    if ((DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 0x48) &&
        DXBALL_CRT_IO_RECORD(block, record_offset)->lookahead != '\n') {
        *input++ = (char)DXBALL_CRT_IO_RECORD(block, record_offset)->lookahead;
        --bytes;
        transfer.total = 1;
        DXBALL_CRT_IO_RECORD(block, record_offset)->lookahead = '\n';
    }
    if (!ReadFile(DXBALL_CRT_IO_RECORD(block, record_offset)->handle,
                  input, bytes, &transfer.read, NULL)) {
        DxBallCrtDword error = GetLastError();
        if (error == 5) {
            _doserrno = error;
            errno = 9;
            return -1;
        }
        if (error == 109) return 0;
        dxball_crt_map_os_error(error);
        return -1;
    }
    transfer.total += transfer.read;
    if (DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 0x80) {
        if (transfer.read != 0 && *(char *)buffer == '\n')
            DXBALL_CRT_IO_RECORD(block, record_offset)->flags |= 4;
        else
            DXBALL_CRT_IO_RECORD(block, record_offset)->flags &= 0xfb;
        transfer.end = (char *)buffer + transfer.total;
        input = (char *)buffer;
        output = (char *)buffer;
        while (input < transfer.end) {
            char value = *input;
            if (value == 0x1a) {
                if ((DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 0x40) == 0)
                    DXBALL_CRT_IO_RECORD(block, record_offset)->flags |= 2;
                break;
            }
            if (value != '\r') {
                ++input;
                *output = value;
                goto advance_output;
            }
            if (input < transfer.end - 1) {
                if (input[1] == '\n') {
                    input += 2;
                    *output = '\n';
                } else {
                    ++input;
                    *output = value;
                }
                goto advance_output;
            }
            ++input;
            transfer.total = 0;
            if (!ReadFile(DXBALL_CRT_IO_RECORD(block, record_offset)->handle,
                          &next, 1, &transfer.read, NULL)) transfer.total = GetLastError();
            if (transfer.total != 0 || transfer.read == 0) goto preserve_cr;
            if (DXBALL_CRT_IO_RECORD(block, record_offset)->flags & 0x48) {
                if (next == '\n') {
                    *output = '\n';
                    goto advance_output;
                }
                *output++ = '\r';
                DXBALL_CRT_IO_RECORD(block, record_offset)->lookahead = (unsigned char)next;
                goto scan_next;
            }
            if (output == (char *)buffer && next == '\n') {
                *output = '\n';
                goto advance_output;
            }
            dxball_crt_seek(descriptor, -1, 1);
            if (next == '\n') goto scan_next;
preserve_cr:
            *output = '\r';
advance_output:
            ++output;
scan_next:
            ;
        }
        transfer.total = (DxBallCrtDword)(output - (char *)buffer);
    }
    return (int)transfer.total;
bad_descriptor:
    errno = 9;
    _doserrno = 0;
    return -1;
}
