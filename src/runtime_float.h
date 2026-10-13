#ifndef DXBALL_RUNTIME_FLOAT_H
#define DXBALL_RUNTIME_FLOAT_H

/* CRT extended conversion storage, not the host's long double representation. */
typedef struct DxBallExtended12 { unsigned char bytes[12]; } DxBallExtended12;
typedef struct DxBallMathException {
    int type;
    char *name;
    double arg1, arg2, retval;
} DxBallMathException;

#ifdef __cplusplus
extern "C" {
#endif

/* Original CRT dependencies. Their maintained bodies remain to be recovered. */
int _strgtold12(DxBallExtended12 *value, const char **end, const char *text,
               int option1, int option2, int option3, int option4);
int _ld12tod(const DxBallExtended12 *value, double *result);
int _ld12tof(const DxBallExtended12 *value, float *result);

int dxball_ascii_to_double(double *result, const char *text);
int dxball_ascii_to_float(float *result, const char *text);
int dxball_math_error(DxBallMathException *exception);

#ifdef __cplusplus
}
#endif
#endif
