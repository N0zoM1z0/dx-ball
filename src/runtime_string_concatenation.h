#ifndef DXBALL_RUNTIME_STRING_CONCATENATION_H
#define DXBALL_RUNTIME_STRING_CONCATENATION_H
#ifdef __cplusplus
extern "C" {
#endif
/* Backed nonoverlapping strings and destination capacity are required. Aligned
   source words, and destination words scanned by strcat, remain readable through
   the word containing NUL, including its trailing bytes. No word is over-stored. */
char *dxball_crt_strcpy(char *destination, const char *source);
char *dxball_crt_strcat(char *destination, const char *source);
#ifdef __cplusplus
}
#endif
#endif
