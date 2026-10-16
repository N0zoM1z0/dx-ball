#include "runtime_cpp_terminal.h"

/* The complete hooks.obj data record is at 0x0042389C. */
DxBallCppTranslator __pSETranslator = 0;
DxBallCppTerminalHandler dxball_cpp_terminate_handler = 0;
DxBallCppTerminalHandler dxball_cpp_unexpected_handler = dxball_cpp_terminate;
DxBallCppTerminalHandler dxball_cpp_inconsistency_handler = dxball_cpp_terminate;

/* FUNCTION: DXBALL 0x0041BC60 */
void dxball_cpp_terminate(void)
{
    __try {
        if (dxball_cpp_terminate_handler != 0) {
            __try {
                dxball_cpp_terminate_handler();
            } __except (1) {
            }
        }
    } __finally {
        dxball_crt_abort();
    }
}

/* FUNCTION: DXBALL 0x0041BCE0 */
void dxball_cpp_inconsistency(void)
{
    __try {
        if (dxball_cpp_inconsistency_handler != 0) {
            __try {
                dxball_cpp_inconsistency_handler();
            } __except (1) {
            }
        }
    } __finally {
        dxball_cpp_terminate();
    }
}
