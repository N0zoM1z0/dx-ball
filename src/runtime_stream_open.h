#ifndef DXBALL_RUNTIME_STREAM_OPEN_H
#define DXBALL_RUNTIME_STREAM_OPEN_H

#include "runtime_stream_transfer.h"

/* The original SECURITY_ATTRIBUTES ABI, with native-width pointers. */
typedef struct DxBallCrtSecurityAttributes {
    DxBallCrtDword length;
    void *descriptor;
    int inherit;
} DxBallCrtSecurityAttributes;

#ifdef __cplusplus
extern "C" {
#endif
extern int dxball_crt_default_commit;
extern int dxball_crt_default_file_mode;
extern int dxball_crt_creation_mask;

DXBALL_CRT_IMPORT void *DXBALL_CRT_OS_CALL CreateFileA(const char *name,
    DxBallCrtDword access, DxBallCrtDword sharing,
    DxBallCrtSecurityAttributes *security, DxBallCrtDword disposition,
    DxBallCrtDword attributes, void *template_file);
DXBALL_CRT_IMPORT DxBallCrtDword DXBALL_CRT_OS_CALL GetFileType(void *handle);

int dxball_crt_allocate_descriptor(void);
int dxball_crt_sopen(const char *filename, int flags, int sharing, ...);
int dxball_crt_chsize(int descriptor, DxBallCrtLong size);
DxBallCrtStream *dxball_crt_open_file(const char *filename, const char *mode,
                                   int sharing, DxBallCrtStream *stream);
DxBallCrtStream *dxball_crt_fsopen(const char *filename, const char *mode, int sharing);
DxBallCrtStream *dxball_crt_fopen(const char *filename, const char *mode);
#ifdef __cplusplus
}
#endif
#endif
