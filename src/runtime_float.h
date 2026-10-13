#ifndef DXBALL_RUNTIME_FLOAT_H
#define DXBALL_RUNTIME_FLOAT_H

/* The Win32 CRT record retains a sixteen-bit rounding tail below its mantissa. */
#pragma pack(push, 2)
typedef struct DxBallExtended12 {
    unsigned short extra;
    unsigned int low, high;
    unsigned short exponent;
} DxBallExtended12;
#pragma pack(pop)
typedef char DxBallExtended12MustBe12[(sizeof(DxBallExtended12) == 12) ? 1 : -1];

typedef struct DxBallBinaryFormat {
    int max_exponent, min_exponent, precision, exponent_bits, destination_bits, bias;
} DxBallBinaryFormat;
typedef char DxBallBinaryFormatMustBe24[(sizeof(DxBallBinaryFormat) == 24) ? 1 : -1];
typedef struct DxBallMathException {
    int type;
    char *name;
    double arg1, arg2, retval;
} DxBallMathException;

#ifdef __cplusplus
extern "C" {
#endif

/* Decimal parsing dependency; its maintained body remains to be recovered. */
int _strgtold12(DxBallExtended12 *value, const char **end, const char *text,
               int option1, int option2, int option3, int option4);

/* Recovered binary conversion entry points. */
int _ld12tod(const DxBallExtended12 *value, double *result);
int _ld12tof(const DxBallExtended12 *value, float *result);
int _ld12cvt(const DxBallExtended12 *value, void *result,
            const DxBallBinaryFormat *format);

/* The three limbs are ordered from most to least significant. Bit positions
   count from the most significant bit of limb zero. */
int _ZeroTail(const unsigned int *mantissa, int position);
int _IncMan(unsigned int *mantissa, int position);
void _CopyMan(unsigned int *destination, const unsigned int *source);
void _FillZeroMan(unsigned int *mantissa);
int _IsZeroMan(const unsigned int *mantissa);
int _RoundMan(unsigned int *mantissa, int precision);
void _ShrMan(unsigned int *mantissa, int bits);
int __addl(unsigned int left, unsigned int right, unsigned int *result);

/* Decimal arithmetic uses the opposite limb order: least significant first. */
void __add_12(unsigned int *left, const unsigned int *right);
void __shl_12(unsigned int *mantissa);
void __shr_12(unsigned int *mantissa);

int dxball_ascii_to_double(double *result, const char *text);
int dxball_ascii_to_float(float *result, const char *text);
int dxball_math_error(DxBallMathException *exception);

#ifdef __cplusplus
}
#endif
#endif
