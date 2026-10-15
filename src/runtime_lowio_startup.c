#include "runtime_lowio_startup.h"

int _nhandle;
DxBallLowioRecord *__pioinfo[64];

/* FUNCTION: DXBALL 0x0041AD10 */
void dxball_crt_initialize_lowio(void)
{
    DxBallCrtStartupInfo startup;
    int count;
    int descriptor;
    int block_index;
    DxBallLowioRecord *record;
    unsigned char *flags;
    const DxBallCrtInheritedHandle *handles;
    void *standard_handle;
    DxBallCrtDword type;

    if ((record = (DxBallLowioRecord *)dxball_runtime_malloc(32 * sizeof(*record))) == NULL)
        dxball_crt_amsg_exit(27);
    __pioinfo[0] = record;
    _nhandle = 32;
    for (; record < __pioinfo[0] + 32; ++record) {
        record->flags = 0;
        record->handle = (void *)(ptrdiff_t)-1;
        record->lookahead = '\n';
    }
    GetStartupInfoA(&startup);
    if (startup.reserved_count != 0 && startup.reserved_data != NULL) {
        count = ((const DxBallCrtInheritedCount *)startup.reserved_data)->value;
        flags = startup.reserved_data + sizeof(int);
        handles = (const DxBallCrtInheritedHandle *)(flags + count);
        count = count < 2048 ? count : 2048;
        for (block_index = 1; _nhandle < count; ++block_index) {
            if ((record = (DxBallLowioRecord *)dxball_runtime_malloc(32 * sizeof(*record))) == NULL) {
                count = _nhandle;
                break;
            }
            __pioinfo[block_index] = record;
            _nhandle += 32;
            for (; record < __pioinfo[block_index] + 32; ++record) {
                record->flags = 0;
                record->handle = (void *)(ptrdiff_t)-1;
                record->lookahead = '\n';
            }
        }
        for (descriptor = 0; descriptor < count; ++descriptor, ++flags, ++handles) {
            if (handles->value != -1 && (*flags & 1) && GetFileType((void *)handles->value)) {
                record = &__pioinfo[descriptor >> 5][descriptor & 31];
                record->handle = (void *)handles->value;
                record->flags = *flags;
            }
        }
    }
    for (descriptor = 0; descriptor < 3; ++descriptor) {
        record = __pioinfo[0] + descriptor;
        if (record->handle == (void *)(ptrdiff_t)-1) {
            record->flags = 0x81;
            if ((standard_handle = GetStdHandle(descriptor == 0 ? (DxBallCrtDword)-10 :
                                                (descriptor == 1 ? (DxBallCrtDword)-11 :
                                                 (DxBallCrtDword)-12))) != (void *)(ptrdiff_t)-1 &&
                (type = GetFileType(standard_handle)) != 0) {
                record->handle = standard_handle;
                if ((type & 255) == 2) record->flags |= 0x40;
                else if ((type & 255) == 3) record->flags |= 8;
            } else {
                record->flags |= 0x40;
            }
        } else {
            record->flags |= 0x80;
        }
    }
    SetHandleCount((unsigned int)_nhandle);
}
