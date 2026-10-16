#include "runtime_entry.h"
#include <excpt.h>

unsigned int _osver = 0, _winver = 0, _winmajor = 0, _winminor = 0;
char *_acmdln;

/* FUNCTION: DXBALL 0x004187A0 */
void dxball_crt_startup(void)
{
    int result;
    unsigned char *command;
    DxBallCrtStartupInfo startup;

    _osver = GetVersion();
    _winminor = (_osver >> 8) & 0xff;
    _winmajor = _osver & 0xff;
    _winver = (_winmajor << 8) + _winminor;
    _osver = (_osver >> 16) & 0xffff;
    dxball_initialize_runtime_heap();
    __try {
        dxball_crt_initialize_lowio();
        dxball_crt_initialize_mbctype();
        _acmdln = GetCommandLineA();
        _aenvptr = dxball_crt_environment_strings();
        if (!_aenvptr || !_acmdln)
            dxball_crt_exit((unsigned int)-1);
        dxball_crt_setargv();
        dxball_crt_setenvp();
        dxball_crt_initialize_runtime();

        command = (unsigned char *)_acmdln;
        if (*command == '"') {
            while (*++command != '"' && *command) {
                if (dxball_crt_ismbblead(*command))
                    ++command;
            }
            if (*command == '"')
                ++command;
        } else {
            while (*command > ' ')
                ++command;
        }
        while (*command && *command <= ' ')
            ++command;
        startup.flags = 0;
        GetStartupInfoA(&startup);
        result = (int)dxball_win_main((DxBallHandle)GetModuleHandleA(0), 0,
            (DxBallHandle)command, startup.flags & 1 ? startup.show : 10);
        dxball_crt_exit(result);
    } __except (dxball_crt_exception_filter(_exception_code(),
            (DxBallCrtExceptionPointers *)_exception_info())) {
        dxball_crt_quick_exit(_exception_code());
    }
}
