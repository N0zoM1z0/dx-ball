#include "allocator.h"
#include "file.h"
#include <string.h>

/* Shared Kernel32 services used by file loading and MDS mapping. */
DxBallHandle (DXBALL_DDCALL *dxball_file_create)(const char *, DxBallUInt,
    DxBallUInt, void *, DxBallUInt, DxBallUInt, DxBallHandle);
DxBallUInt (DXBALL_DDCALL *dxball_file_size)(DxBallHandle, DxBallUInt *);
DxBallInt (DXBALL_DDCALL *dxball_file_read)(DxBallHandle, void *,
    DxBallUInt, DxBallUInt *, void *);
DxBallInt (DXBALL_DDCALL *dxball_file_close)(DxBallHandle);
const char dxball_file_fallback_prefix[] = "..\\";


/* FUNCTION: DXBALL 0x00403320 */
void *dxball_load_binary_file(const char *path, void *destination, DxBallInt allocate)
{
    DxBallUInt read;
    {
        struct {
            DxBallUInt bytes;
            DxBallHandle handle;
            char fallback[260];
        } file;
        file.handle = dxball_file_create(path, 0x80000000UL, 1, NULL, 3, 0x80, 0);
        if (file.handle == (DxBallHandle)-1) {
            strcpy(file.fallback, dxball_file_fallback_prefix);
            strcat(file.fallback, path);
            file.handle = dxball_file_create(file.fallback, 0x80000000UL, 1, NULL, 3, 0x80, 0);
            if (file.handle == (DxBallHandle)-1) return NULL;
        }
        file.bytes = dxball_file_size(file.handle, NULL);
        if (allocate != 0) {
            destination = dxball_runtime_malloc(file.bytes);
            if (destination == NULL) return NULL;
        }
        if (!dxball_file_read(file.handle, destination, file.bytes, &read, NULL)) {
            dxball_heap_release(destination);
            return NULL;
        }
        dxball_file_close(file.handle);
        return destination;
    }
}
