#include "runtime_locale_backends.h"

extern "C" {

static const unsigned short empty_wide[2] = {0, 0};

/* FUNCTION: DXBALL 0x0041E000 */
int __crtGetStringTypeA(DxBallCrtLocaleWord type, const char *input,
                       int input_count, unsigned short *output,
                       int code_page, DxBallCrtLocaleWord locale)
{
    static int classification_api;
    unsigned short probe_type;
    unsigned short *wide_input;
    int wide_count;
    int result;
    if (classification_api == 0) {
        if (GetStringTypeA(0, 1, "\0", 1, &probe_type)) classification_api = 2;
        else if (GetStringTypeW(1, empty_wide, 1, &probe_type)) classification_api = 1;
        else return 0;
    }
    if (classification_api == 2) {
        if (locale == 0) locale = __lc_handle[2];
        return GetStringTypeA(locale, type, input, input_count, output);
    }
    if (classification_api != 1) return classification_api;
    result = 0;
    wide_input = 0;
    if (code_page == 0) code_page = (int)__lc_codepage;
    wide_count = MultiByteToWideChar((unsigned int)code_page, 9, input, input_count, 0, 0);
    if (wide_count != 0) {
        wide_input = (unsigned short *)dxball_runtime_calloc(2, (DxBallUInt)wide_count);
        if (wide_input != 0) {
            wide_count = MultiByteToWideChar((unsigned int)code_page, 1, input,
                                             input_count, wide_input, wide_count);
            if (wide_count != 0) result = GetStringTypeW(type, wide_input, wide_count, output);
        }
    }
    dxball_heap_release(wide_input);
    return result;
}

}
