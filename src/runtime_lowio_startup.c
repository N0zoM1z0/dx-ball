#include "runtime_lowio_startup.h"

int _nhandle;
DxBallLowioRecord *__pioinfo[64];

/* FUNCTION: DXBALL 0x0041AD10 */
void dxball_crt_initialize_lowio(void)
{
    DxBallCrtStartupInfo startup;
    DxBallLowioRecord *record;
    DxBallLowioRecord **block;
    int count;
    int index;
    unsigned char *flags;
    unsigned char *handles;
    record = (DxBallLowioRecord *)dxball_runtime_malloc(32 * sizeof(*record));
    if (record == 0) dxball_crt_amsg_exit(27);
    __pioinfo[0] = record;
    _nhandle = 32;
    for (; record < __pioinfo[0] + 32; ++record) {
        record->flags = 0;
        record->handle = (void *)(ptrdiff_t)-1;
        record->lookahead = '\n';
    }
    GetStartupInfoA(&startup);
    if (startup.reserved_count != 0 && startup.reserved_data != 0) {
        count = ((const DxBallCrtInheritedCount *)startup.reserved_data)->value;
        flags = startup.reserved_data + sizeof(count);
        handles = flags + count;
        if (count >= 2048) count = 2048;
        for (block = __pioinfo + 1; count > _nhandle; ++block) {
            record = (DxBallLowioRecord *)dxball_runtime_malloc(32 * sizeof(*record));
            if (record == 0) {
                count = _nhandle;
                break;
            }
            *block = record;
            _nhandle += 32;
            for (; record < *block + 32; ++record) {
                record->flags = 0;
                record->handle = (void *)(ptrdiff_t)-1;
                record->lookahead = '\n';
            }
        }
        for (index = 0; index < count; ++index, ++flags, handles += sizeof(DxBallCrtOsHandle)) {
            DxBallCrtOsHandle inherited;
            /* Serialized handles can start at an unaligned address. */
            inherited = ((const DxBallCrtInheritedHandle *)handles)->value;
            if (inherited != -1 && (*flags & 1) && GetFileType((void *)inherited)) {
                inherited = ((const DxBallCrtInheritedHandle *)handles)->value;
                record = &__pioinfo[index >> 5][index & 31];
                record->handle = (void *)inherited;
                record->flags = *flags;
            }
        }
    }
    for (index = 0; index < 3; ++index) {
        record = &__pioinfo[0][index];
        if (record->handle == (void *)(ptrdiff_t)-1) {
            void *handle;
            DxBallCrtDword type;
            DxBallCrtDword standard;
            record->flags = 0x81;
            if (index == 0) standard = (DxBallCrtDword)-10;
            else if (index == 1) standard = (DxBallCrtDword)-11;
            else standard = (DxBallCrtDword)-12;
            handle = GetStdHandle(standard);
            if (handle == (void *)(ptrdiff_t)-1 || (type = GetFileType(handle)) == 0)
                record->flags |= 0x40;
            else {
                record->handle = handle;
                if ((type & 255) == 2) record->flags |= 0x40;
                else if ((type & 255) == 3) record->flags |= 8;
            }
        } else record->flags |= 0x80;
    }
    SetHandleCount((unsigned int)_nhandle);
}
