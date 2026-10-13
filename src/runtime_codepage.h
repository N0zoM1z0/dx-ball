#ifndef DXBALL_RUNTIME_CODEPAGE_H
#define DXBALL_RUNTIME_CODEPAGE_H

#include "runtime_multibyte.h"

typedef struct DxBallCrtCodePageInfo {
    unsigned int max_character_size;
    unsigned char default_character[2];
    unsigned char lead_bytes[12];
} DxBallCrtCodePageInfo;
typedef char DxBallCrtCodePageInfoMustBe20[(sizeof(DxBallCrtCodePageInfo) == 20) ? 1 : -1];

#if defined(_MSC_VER)
#define DXBALL_CODEPAGE_IMPORT __declspec(dllimport)
#define DXBALL_CODEPAGE_CALL __stdcall
#elif defined(_WIN32)
#define DXBALL_CODEPAGE_IMPORT __attribute__((dllimport))
#define DXBALL_CODEPAGE_CALL __attribute__((stdcall))
#else
#define DXBALL_CODEPAGE_IMPORT
#define DXBALL_CODEPAGE_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int __mbcodepage;
extern unsigned int __mblcid;
extern unsigned short __mbulinfo[6];
extern unsigned int __lc_codepage;

DXBALL_CODEPAGE_IMPORT unsigned int DXBALL_CODEPAGE_CALL GetACP(void);
DXBALL_CODEPAGE_IMPORT unsigned int DXBALL_CODEPAGE_CALL GetOEMCP(void);
DXBALL_CODEPAGE_IMPORT int DXBALL_CODEPAGE_CALL GetCPInfo(unsigned int code_page,
                                                       DxBallCrtCodePageInfo *info);

int dxball_crt_setmbcp(int code_page);
void dxball_crt_initialize_mbctype(void);

#ifdef __cplusplus
}
#endif
#endif
