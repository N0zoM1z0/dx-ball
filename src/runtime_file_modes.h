#ifndef DXBALL_RUNTIME_FILE_MODES_H
#define DXBALL_RUNTIME_FILE_MODES_H

/* Original low-I/O records have an eight-byte stride. Only byte four is
   accessed here; the other bytes remain owned by the low-I/O runtime. */
typedef struct DxBallLowioRecord {
    unsigned char bytes[8];
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
