#include "runtime_stream_open.h"

/* Shared single-thread CRT error and file-opening state. */
int errno = 0;
DxBallCrtDword _doserrno = 0;
int dxball_crt_creation_mask = 0;
int dxball_crt_default_commit = 0;
int dxball_crt_default_file_mode = 0;

/* FILE objects with descriptor -1 use the same typed low-I/O fallback. */
DxBallLowioRecord dxball_crt_invalid_io = {
    (void *)(ptrdiff_t)-1, 0, '\n'
};
