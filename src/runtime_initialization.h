#ifndef DXBALL_RUNTIME_INITIALIZATION_H
#define DXBALL_RUNTIME_INITIALIZATION_H

#ifdef __cplusplus
extern "C" {
#endif
#include "termination.h"

extern int _fltused, _ldused, __fastflag, _adjust_fdiv;
extern DxBallCrtCallback _FPinit, _FPmtinit, _FPmtterm;
extern DxBallCrtCallback __xi_a[], __xi_z[], __xc_a[], __xc_z[];

/* Genuine remaining conversion/physical-x87 dependencies, not replacement stubs. */
void dxball_crt_initialize_conversion_table(void);
int dxball_crt_test_fdiv_processors(void);
int _clrfp(void);
unsigned int _controlfp(unsigned int value, unsigned int mask);

void dxball_crt_initialize_runtime(void);
void dxball_crt_initialize_math(void);
void dxball_crt_fp_thread_noop(void);
void dxball_crt_set_default_precision(void);

#ifdef __cplusplus
}
#endif
#endif
