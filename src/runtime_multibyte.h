#ifndef DXBALL_RUNTIME_MULTIBYTE_H
#define DXBALL_RUNTIME_MULTIBYTE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Shared CRT tables: EOF slot followed by the 256 unsigned-byte entries. */
extern unsigned char _mbctype[257];
extern unsigned short _ctype[257];
int dxball_crt_ismbblead(unsigned int character);

#ifdef __cplusplus
}
#endif
#endif
