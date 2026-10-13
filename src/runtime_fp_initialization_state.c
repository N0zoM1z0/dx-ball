#include "runtime_initialization.h"

/* Four Win32 words and three actual callback slots; native pointers grow. */
int _fltused = 0x9875;
int _ldused = 0x9873;
int __fastflag = 0;
int _adjust_fdiv = 0;
DxBallCrtCallback _FPinit = dxball_crt_initialize_math;
DxBallCrtCallback _FPmtinit = dxball_crt_fp_thread_noop;
DxBallCrtCallback _FPmtterm = dxball_crt_fp_thread_noop;
