#ifndef DXBALL_RUNTIME_FLOAT_FORMAT_H
#define DXBALL_RUNTIME_FLOAT_FORMAT_H

#include "runtime_float.h"

typedef struct DxBallCrtFloatText {
    int sign, decimal_position, flags;
    char *mantissa;
} DxBallCrtFloatText;

/* Before conversion initialization only the unavailable member is active.
   Initialization publishes each genuine callback with its own signature. */
typedef union DxBallCrtFloatConvertSlot {
    void (*unavailable)(void);
    void (*active)(const double *, char *, int, int, int);
} DxBallCrtFloatConvertSlot;
typedef union DxBallCrtFloatStringSlot {
    void (*unavailable)(void);
    void (*active)(char *);
} DxBallCrtFloatStringSlot;
typedef union DxBallCrtFloatAssignSlot {
    void (*unavailable)(void);
    void (*active)(int, void *, const char *);
} DxBallCrtFloatAssignSlot;
typedef union DxBallCrtFloatPositiveSlot {
    void (*unavailable)(void);
    int (*active)(const double *);
} DxBallCrtFloatPositiveSlot;
typedef struct DxBallCrtFloatCallbacks {
    DxBallCrtFloatConvertSlot convert;
    DxBallCrtFloatStringSlot crop;
    DxBallCrtFloatAssignSlot assign;
    DxBallCrtFloatStringSlot force_decimal;
    DxBallCrtFloatPositiveSlot positive;
    DxBallCrtFloatConvertSlot convert_compat;
} DxBallCrtFloatCallbacks;
typedef char DxBallCrtFloatCallbacksMustBeSixPointers[
    sizeof(DxBallCrtFloatCallbacks) == 6 * sizeof(void (*)(void)) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallCrtFloatCallbacks _cfltcvt_tab;
void dxball_crt_float_unavailable(void);
void dxball_crt_format_float(const double *value, char *buffer,
                              int format, int precision, int capitals);
void dxball_crt_crop_float_zeros(char *buffer);
void dxball_crt_assign_float(int use_double, void *destination, const char *text);
void dxball_crt_force_decimal_point(char *buffer);
int dxball_crt_float_positive(const double *value);
void dxball_crt_float_digits(char *buffer, int digits, DxBallCrtFloatText *value);

/* Genuine remaining formatter bodies; their source is a separate dependency. */
char *dxball_crt_format_exponent(const double *, char *, int, int);
char *dxball_crt_format_fixed(const double *, char *, int);
void dxball_crt_format_general(const double *, char *, int, int);

#ifdef __cplusplus
}
#endif
#endif
