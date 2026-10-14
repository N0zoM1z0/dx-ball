#ifndef DXBALL_RUNTIME_POW_SPECIAL_H
#define DXBALL_RUNTIME_POW_SPECIAL_H
#ifdef __cplusplus
extern "C" {
#endif
/* Handles infinite operands only. Finite/finite leaves result untouched.
   The return distinguishes an indefinite result, not whether result was set. */
int dxball_crt_pow_special(double base, double exponent, double *result);
#ifdef __cplusplus
}
#endif
#endif
