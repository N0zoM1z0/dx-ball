#include "runtime_cpp_filter.h"

/* Retain the original C++ tag in the link name; the shared owner consumes the
   same two-pointer record through its recovered typed view. */
struct _EXCEPTION_POINTERS;
DxBallCrtLong DXBALL_CRT_OS_CALL __CxxUnhandledExceptionFilter(
    _EXCEPTION_POINTERS *pointers)
{
    return dxball_cpp_unhandled_filter(
        reinterpret_cast<DxBallCppExceptionPointers *>(pointers));
}

/* The remaining frame transport calls these original C++ interfaces. */
void terminate(void) { dxball_cpp_terminate(); }
void _inconsistency(void) { dxball_cpp_inconsistency(); }
