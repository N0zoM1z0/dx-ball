#ifndef DXBALL_RUNTIME_LOCALE_BACKENDS_H
#define DXBALL_RUNTIME_LOCALE_BACKENDS_H

#include "runtime_case_conversion.h"

#ifdef _WIN32
#define DXBALL_LOCALE_IMPORT __declspec(dllimport)
#define DXBALL_LOCALE_OS_CALL __stdcall
#else
#define DXBALL_LOCALE_IMPORT
#define DXBALL_LOCALE_OS_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The maintained allocator/resize owners are C translation units. */
#include "runtime_resize.h"

extern unsigned int __lc_codepage;

DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL LCMapStringA(
    DxBallCrtLocaleWord locale, DxBallCrtLocaleWord flags, const char *input,
    int input_count, char *output, int output_count);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL LCMapStringW(
    DxBallCrtLocaleWord locale, DxBallCrtLocaleWord flags, const unsigned short *input,
    int input_count, unsigned short *output, int output_count);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL GetStringTypeA(
    DxBallCrtLocaleWord locale, DxBallCrtLocaleWord type, const char *input,
    int input_count, unsigned short *output);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL GetStringTypeW(
    DxBallCrtLocaleWord type, const unsigned short *input, int input_count,
    unsigned short *output);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL MultiByteToWideChar(
    unsigned int code_page, DxBallCrtLocaleWord flags, const char *input,
    int input_count, unsigned short *output, int output_count);
DXBALL_LOCALE_IMPORT int DXBALL_LOCALE_OS_CALL WideCharToMultiByte(
    unsigned int code_page, DxBallCrtLocaleWord flags, const unsigned short *input,
    int input_count, char *output, int output_count, const char *default_character,
    int *used_default);

#ifdef __cplusplus
}
#endif
#endif
