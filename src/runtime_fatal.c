#include "runtime_fatal.h"
#include <string.h>

int dxball_crt_error_mode;
int dxball_crt_application_type = 2;
DxBallCrtCallback dxball_crt_debug_message;
DxBallCrtExitRoutine dxball_crt_exit_routine = dxball_crt_quick_exit;

typedef struct DxBallRuntimeError {
    int reason;
    const char *text;
} DxBallRuntimeError;

static DxBallRuntimeError runtime_errors[17] = {
    {2, "R6002\r\n- floating point not loaded\r\n"},
    {8, "R6008\r\n- not enough space for arguments\r\n"},
    {9, "R6009\r\n- not enough space for environment\r\n"},
    {10, "\r\nabnormal program termination\r\n"},
    {16, "R6016\r\n- not enough space for thread data\r\n"},
    {17, "R6017\r\n- unexpected multithread lock error\r\n"},
    {18, "R6018\r\n- unexpected heap error\r\n"},
    {19, "R6019\r\n- unable to open console device\r\n"},
    {24, "R6024\r\n- not enough space for _onexit/atexit table\r\n"},
    {25, "R6025\r\n- pure virtual function call\r\n"},
    {26, "R6026\r\n- not enough space for stdio initialization\r\n"},
    {27, "R6027\r\n- not enough space for lowio initialization\r\n"},
    {120, "DOMAIN error\r\n"},
    {121, "SING error\r\n"},
    {122, "TLOSS error\r\n"},
    {252, "\r\n"},
    {255, "runtime error "}
};

/* FUNCTION: DXBALL 0x00418930 */
void dxball_crt_amsg_exit(int reason)
{
    if (dxball_crt_error_mode == 1) dxball_crt_error_banner();
    dxball_crt_write_error(reason);
    dxball_crt_exit_routine(255);
}

/* FUNCTION: DXBALL 0x0041C800 */
void dxball_crt_error_banner(void)
{
    if (dxball_crt_error_mode == 1 ||
        (dxball_crt_error_mode == 0 && dxball_crt_application_type == 1)) {
        dxball_crt_write_error(252);
        if (dxball_crt_debug_message) dxball_crt_debug_message();
        dxball_crt_write_error(255);
    }
}

/* FUNCTION: DXBALL 0x0041C840 */
void dxball_crt_write_error(int reason)
{
    int index;
    DxBallCrtDword written;
    for (index = 0; (size_t)index < sizeof(runtime_errors) / sizeof(runtime_errors[0]); ++index) {
        if (reason == runtime_errors[index].reason) break;
    }
    if (runtime_errors[index].reason == reason) {
        if (dxball_crt_error_mode == 1 ||
            (dxball_crt_error_mode == 0 && dxball_crt_application_type == 1)) {
            void *handle = __pioinfo[0][2].handle;
            if (handle == (void *)(ptrdiff_t)-1) handle = GetStdHandle((DxBallCrtDword)-12);
            WriteFile(handle, runtime_errors[index].text,
                      (DxBallCrtDword)strlen(runtime_errors[index].text), &written, 0);
        } else if (reason != 252) {
            char *name;
            char program[260];
            char message[60 + 100];
            if (!GetModuleFileNameA(0, program, sizeof(program)))
                strcpy(program, "<program name unknown>");
            name = program;
            if (strlen(name) + 1 > 60) {
                name = program + strlen(program) - 60 + 1;
                strncpy(name, "...", 3);
            }
            strcpy(message, "Runtime Error!\n\nProgram: ");
            strcat(message, name);
            strcat(message, "\n\n");
            strcat(message, runtime_errors[index].text);
            __crtMessageBoxA(message, "Microsoft Visual C++ Runtime Library", 0x12010);
        }
    }
}
