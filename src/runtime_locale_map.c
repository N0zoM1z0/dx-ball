#include "runtime_locale_backends.h"

static const unsigned short empty_wide[2] = {0, 0};

/* FUNCTION: DXBALL 0x0041AC40 */
static DxBallUInt dxball_crt_strncnt(const char *input, DxBallUInt count)
{
    const char *cursor = input;
    DxBallUInt remaining = count;
    while (remaining-- && *cursor) ++cursor;
    /* The original also reads the sentinel when the bound is exhausted. */
    if (*cursor == 0) return (DxBallUInt)(cursor - input);
    return count;
}

/* FUNCTION: DXBALL 0x0041AA10 */
int __crtLCMapStringA(DxBallCrtLocaleWord locale, DxBallCrtLocaleWord flags,
                     const char *input, int input_count, char *output,
                     int output_count, int code_page)
{
    static int mapping_api;
    if (mapping_api == 0) {
        if (LCMapStringA(0, 0x100, "\0", 1, 0, 0)) mapping_api = 2;
        else if (LCMapStringW(0, 0x100, empty_wide, 1, 0, 0)) mapping_api = 1;
        else return 0;
    }
    if (input_count > 0)
        input_count = (int)dxball_crt_strncnt(input, (DxBallUInt)input_count);
    if (mapping_api == 2)
        return LCMapStringA(locale, flags, input, input_count, output, output_count);
    if (mapping_api != 1) return mapping_api;
    {
    unsigned short *wide_input;
    unsigned short *wide_output;
    int wide_count;
    int result;
    wide_output = 0;
    if (code_page == 0) code_page = (int)__lc_codepage;
    wide_count = MultiByteToWideChar((unsigned int)code_page, 9, input, input_count, 0, 0);
    if (wide_count == 0) return 0;
    wide_input = (unsigned short *)dxball_runtime_malloc((DxBallUInt)wide_count * 2);
    if (wide_input == 0) return 0;
    if (!MultiByteToWideChar((unsigned int)code_page, 1, input, input_count,
                             wide_input, wide_count)) goto failure;
    result = LCMapStringW(locale, flags, wide_input, wide_count, 0, 0);
    if (result == 0) goto failure;
    if (flags & 0x400) {
        if (output_count == 0) goto success;
        if (output_count < result) goto failure;
        if (!LCMapStringW(locale, flags, wide_input, wide_count,
                           (unsigned short *)output, output_count)) goto failure;
    } else {
        wide_output = (unsigned short *)dxball_runtime_malloc((DxBallUInt)result * 2);
        if (wide_output == 0) goto failure;
        if (!LCMapStringW(locale, flags, wide_input, wide_count,
                           wide_output, result)) goto failure;
        if (output_count == 0) {
            result = WideCharToMultiByte((unsigned int)code_page, 0x220,
                                         wide_output, result, 0, 0, 0, 0);
            if (result == 0) goto failure;
        } else {
            result = WideCharToMultiByte((unsigned int)code_page, 0x220,
                                         wide_output, result, output, output_count, 0, 0);
            if (result == 0) goto failure;
        }
    }
success:
    dxball_heap_release(wide_input);
    dxball_heap_release(wide_output);
    return result;
failure:
    dxball_heap_release(wide_input);
    dxball_heap_release(wide_output);
    return 0;
    }
}
