#ifndef DXBALL_RUNTIME_CASE_CONVERSION_H
#define DXBALL_RUNTIME_CASE_CONVERSION_H

#include "state_types.h"

#ifdef _WIN32
typedef unsigned long DxBallCrtLocaleWord;
#else
typedef DxBallUInt DxBallCrtLocaleWord;
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern DxBallCrtLocaleWord __lc_handle[];
extern int __mb_cur_max;
extern unsigned short *_pctype;

int __crtLCMapStringA(DxBallCrtLocaleWord locale, DxBallCrtLocaleWord flags,
                     const char *input, int input_count, char *output,
                     int output_count, int code_page);
int __crtGetStringTypeA(DxBallCrtLocaleWord type, const char *input,
                       int input_count, unsigned short *output,
                       int code_page, DxBallCrtLocaleWord locale);

int dxball_crt_toupper(int character);
int dxball_crt_tolower(int character);
int _isctype(int character, int mask);

#ifdef __cplusplus
}
#endif
#endif
