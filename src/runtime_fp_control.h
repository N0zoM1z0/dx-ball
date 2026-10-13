#ifndef DXBALL_RUNTIME_FP_CONTROL_H
#define DXBALL_RUNTIME_FP_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned int dxball_crt_abstract_control_word(unsigned short hardware);
unsigned short dxball_crt_hardware_control_word(unsigned int abstract_word);
unsigned int _controlfp(unsigned int value, unsigned int mask);
/* Genuine physical x87 dependency, not a portable replacement body. */
unsigned int _control87(unsigned int value, unsigned int mask);

void dxball_crt_set_math_errno(int error);
int dxball_crt_math_error_code(unsigned int flags);
char *dxball_crt_math_function_name(int function);
double dxball_crt_set_float_exponent(double value, int exponent);
int dxball_crt_float_special_type(double value);

#ifdef __cplusplus
}
#endif
#endif
