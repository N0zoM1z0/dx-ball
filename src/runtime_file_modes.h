#ifndef DXBALL_RUNTIME_FILE_MODES_H
#define DXBALL_RUNTIME_FILE_MODES_H

/* Handle, flags and one-byte lookahead follow the original low-I/O consumers.
   Their natural Win32 layout has the original eight-byte record stride.
   Host handles retain native pointer width; unknown trailing bytes are not fields. */
typedef struct DxBallLowioRecord {
    void *handle;
    unsigned char flags;
    unsigned char lookahead;
} DxBallLowioRecord;

#ifdef __cplusplus
extern "C" {
#endif

extern int _nhandle;
extern DxBallLowioRecord *__pioinfo[];
extern int errno;
int _setmode(int descriptor, int mode);

#ifdef __cplusplus
}
#endif
#endif
