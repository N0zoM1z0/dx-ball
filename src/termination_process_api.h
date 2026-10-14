#ifndef DXBALL_TERMINATION_PROCESS_API_H
#define DXBALL_TERMINATION_PROCESS_API_H
/* Genuine Windows process boundary; native fixtures bind this same API. */
#if defined(_WIN32)
__declspec(dllimport) void __stdcall ExitProcess(unsigned long status);
#else
void ExitProcess(unsigned int status);
#endif
#endif
