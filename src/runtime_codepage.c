#include "runtime_codepage.h"
#include <string.h>

unsigned char _mbctype[257] = {0};
int __mbcodepage = 0;
unsigned int __mblcid = 0;
unsigned short __mbulinfo[6] = {0};

typedef struct DxBallCrtCodePageRanges {
    int code_page;
    unsigned short case_info[6];
    unsigned char ranges[4][8];
} DxBallCrtCodePageRanges;
typedef char DxBallCrtCodePageRangesMustBe48[(sizeof(DxBallCrtCodePageRanges) == 48) ? 1 : -1];

static int system_code_page = 0;
static unsigned char range_flags[4] = {1, 2, 4, 8};
static DxBallCrtCodePageRanges code_page_ranges[5] = {
    {932, {0x8260, 0x8279, 0x21, 0, 0, 0},
     {{0xa6, 0xdf, 0, 0, 0, 0, 0, 0}, {0xa1, 0xa5, 0, 0, 0, 0, 0, 0},
      {0x81, 0x9f, 0xe0, 0xfc, 0, 0, 0, 0}, {0x40, 0x7e, 0x80, 0xfc, 0, 0, 0, 0}}},
    {936, {0xa3c1, 0xa3da, 0x20, 0, 0, 0},
     {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
      {0x81, 0xfe, 0, 0, 0, 0, 0, 0}, {0x40, 0xfe, 0, 0, 0, 0, 0, 0}}},
    {949, {0xa3c1, 0xa3da, 0x20, 0, 0, 0},
     {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
      {0x81, 0xfe, 0, 0, 0, 0, 0, 0}, {0x41, 0xfe, 0, 0, 0, 0, 0, 0}}},
    {950, {0xa2cf, 0xa2e4, 0x1a, 0xa2e5, 0xa2e8, 0x5b},
     {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
      {0x81, 0xfe, 0, 0, 0, 0, 0, 0}, {0x40, 0x7e, 0xa1, 0xfe, 0, 0, 0, 0}}},
    {1361, {0xda51, 0xda5e, 0x20, 0xda5f, 0xda6a, 0x32},
     {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
      {0x81, 0xd3, 0xd8, 0xde, 0xe0, 0xf9, 0, 0}, {0x31, 0x7e, 0x81, 0xfe, 0, 0, 0, 0}}}
};

static int dxball_crt_system_code_page(int code_page)
{
    system_code_page = 0;
    if (code_page == -2) {
        system_code_page = 1;
        return (int)GetOEMCP();
    }
    if (code_page == -3) {
        system_code_page = 1;
        return (int)GetACP();
    }
    if (code_page == -4) {
        system_code_page = 1;
        return __lc_codepage;
    }
    return code_page;
}

static unsigned int dxball_crt_codepage_locale(int code_page)
{
    switch (code_page) {
    case 932: return 0x411;
    case 936: return 0x804;
    case 949: return 0x412;
    case 950: return 0x404;
    default: return 0;
    }
}

static void dxball_crt_set_single_byte(void)
{
    memset(_mbctype, 0, sizeof(_mbctype));
    __mbcodepage = 0;
    __mblcid = 0;
    memset(__mbulinfo, 0, sizeof(__mbulinfo));
}

int dxball_crt_setmbcp(int code_page)
{
    DxBallCrtCodePageInfo info;
    int index;
    unsigned int category, character;
    unsigned char *range;
    code_page = dxball_crt_system_code_page(code_page);
    if (__mbcodepage == code_page)
        return 0;
    if (code_page == 0) {
        dxball_crt_set_single_byte();
        return 0;
    }
    for (index = 0; index < 5; ++index) {
        if (code_page_ranges[index].code_page == code_page) {
            memset(_mbctype, 0, sizeof(_mbctype));
            for (category = 0; category < 4; ++category) {
                range = code_page_ranges[index].ranges[category];
                while (range[0] && range[1]) {
                    for (character = range[0]; character <= range[1]; ++character)
                        _mbctype[character + 1] |= range_flags[category];
                    range += 2;
                }
            }
            __mbcodepage = code_page;
            __mblcid = dxball_crt_codepage_locale(code_page);
            memcpy(__mbulinfo, code_page_ranges[index].case_info, sizeof(__mbulinfo));
            return 0;
        }
    }
    if (GetCPInfo((unsigned int)code_page, &info) == 1) {
        memset(_mbctype, 0, sizeof(_mbctype));
        if (info.max_character_size > 1) {
            range = info.lead_bytes;
            while (range[0] && range[1]) {
                for (character = range[0]; character <= range[1]; ++character)
                    _mbctype[character + 1] |= 4;
                range += 2;
            }
            for (character = 1; character < 0xff; ++character)
                _mbctype[character + 1] |= 8;
            __mbcodepage = code_page;
            __mblcid = dxball_crt_codepage_locale(code_page);
        } else {
            __mbcodepage = 0;
            __mblcid = 0;
        }
        memset(__mbulinfo, 0, sizeof(__mbulinfo));
        return 0;
    }
    if (system_code_page) {
        dxball_crt_set_single_byte();
        return 0;
    }
    return -1;
}

void dxball_crt_initialize_mbctype(void)
{
    dxball_crt_setmbcp(-3);
}
