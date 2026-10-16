/* Original VC4 names bound to shared recovered implementations. These adapters
   are integration glue, not additional recovered original function bodies. */
#include "allocator.h"
#include "termination.h"
#include "runtime_absolute.h"
#include "runtime_absolute_double.h"
#include "runtime_access.h"
#include "runtime_case_conversion.h"
#include "runtime_integer_text.h"
#include "runtime_memory_copy.h"
#include "runtime_memory_fill.h"
#include "runtime_string_concatenation.h"
#include "runtime_string_copy.h"
#include "runtime_string_length.h"
#include "runtime_stream_open.h"
#include "runtime_stream_operations.h"
#include "runtime_error_control.h"
#include "runtime_onexit.h"
#include "runtime_pow_special.h"
#include "runtime_x87_bridge.h"

typedef char RequiresI686[(sizeof(void *) == 4 && sizeof(size_t) == 4) ? 1 : -1];

void exit(int status) { dxball_crt_exit((unsigned int)status); }
void _exit(int status) { dxball_crt_quick_exit((unsigned int)status); }
void _amsg_exit(int reason) { dxball_crt_amsg_exit(reason); }
void _NMSG_WRITE(int reason) { dxball_crt_write_error(reason); }
void _FF_MSGBANNER(void) { dxball_crt_error_banner(); }
void abort(void) { dxball_crt_abort(); }
int raise(int signal_number) { return dxball_crt_raise(signal_number); }
int atexit(DxBallCrtCallback callback) { return dxball_crt_atexit(callback); }
DxBallOnExitCallback _onexit(DxBallOnExitCallback callback)
{ return dxball_crt_onexit(callback); }
int _matherr(DxBallMathException *exception) { return dxball_math_error(exception); }
int _powhlp(double base, double exponent, double *result)
{ return dxball_crt_pow_special(base, exponent, result); }
void _87except(int operation, DxBallMathException *exception,
               const unsigned short *control_word)
{ dxball_crt_x87_exception_bridge(operation, exception, control_word); }
void *malloc(size_t bytes) { return dxball_runtime_malloc((DxBallUInt)bytes); }
void *calloc(size_t count, size_t bytes)
{ return dxball_runtime_calloc((DxBallUInt)count, (DxBallUInt)bytes); }
void *realloc(void *memory, size_t bytes)
{ return dxball_runtime_realloc(memory, (DxBallUInt)bytes); }
size_t _msize(void *memory) { return dxball_runtime_msize(memory); }
void free(void *memory) { dxball_heap_release(memory); }
int abs(int value) { return dxball_crt_absolute(value); }
double fabs(double value) { return dxball_crt_absolute_double(value); }
int _access(const char *path, int mode) { return dxball_crt_access(path, mode); }
int access(const char *path, int mode) { return dxball_crt_access(path, mode); }
int toupper(int value) { return dxball_crt_toupper(value); }
int tolower(int value) { return dxball_crt_tolower(value); }
char *_itoa(int value, char *buffer, int radix)
{ return dxball_crt_itoa(value, buffer, radix); }
char *_ultoa(unsigned long value, char *buffer, int radix)
{ return dxball_crt_ultoa(value, buffer, radix); }
void *memcpy(void *destination, const void *source, size_t count)
{ return dxball_crt_memcpy(destination, source, count); }
void *memmove(void *destination, const void *source, size_t count)
{ return dxball_crt_copy_memory(destination, source, count); }
void *memset(void *destination, int value, size_t count)
{ return dxball_crt_fill_memory(destination, value, count); }
char *strcpy(char *destination, const char *source)
{ return dxball_crt_strcpy(destination, source); }
char *strcat(char *destination, const char *source)
{ return dxball_crt_strcat(destination, source); }
char *strncpy(char *destination, const char *source, size_t count)
{ return dxball_crt_strncpy(destination, source, count); }
size_t strlen(const char *text) { return dxball_crt_string_length(text); }
DxBallCrtStream *fopen(const char *filename, const char *mode)
{ return dxball_crt_fopen(filename, mode); }
int fclose(DxBallCrtStream *stream) { return dxball_crt_fclose(stream); }
size_t fread(void *buffer, size_t size, size_t count, DxBallCrtStream *stream)
{ return dxball_crt_fread(buffer, size, count, stream); }
size_t fwrite(const void *buffer, size_t size, size_t count, DxBallCrtStream *stream)
{ return dxball_crt_fwrite(buffer, size, count, stream); }
int fseek(DxBallCrtStream *stream, long offset, int origin)
{ return dxball_crt_fseek(stream, offset, origin); }
int _filbuf(DxBallCrtStream *stream) { return dxball_crt_fill_input(stream); }
