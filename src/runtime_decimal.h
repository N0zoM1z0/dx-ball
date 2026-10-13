#ifndef DXBALL_RUNTIME_DECIMAL_H
#define DXBALL_RUNTIME_DECIMAL_H

#include "runtime_mantissa_arithmetic.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Original locale/classification dependencies; supplied by the runtime. */
extern int __mb_cur_max;
extern char __decimal_point;
extern unsigned short *_pctype;
int _isctype(int character, int mask);

extern const DxBallExtended12 _pow10pos[29];
extern const DxBallExtended12 _pow10neg[29];
void __ld12mul(DxBallExtended12 *left, const DxBallExtended12 *right);
void __multtenpow12(DxBallExtended12 *value, int exponent, int keep_tail);

#ifdef __cplusplus
}
#endif
#endif
