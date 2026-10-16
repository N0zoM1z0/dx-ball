#ifndef DXBALL_RUNTIME_CPP_TERMINAL_H
#define DXBALL_RUNTIME_CPP_TERMINAL_H

#include "runtime_cpp_tables.h"

typedef void (*DxBallCppTerminalHandler)(void);

extern "C" {
extern DxBallCppTerminalHandler dxball_cpp_terminate_handler;
extern DxBallCppTerminalHandler dxball_cpp_unexpected_handler;
extern DxBallCppTerminalHandler dxball_cpp_inconsistency_handler;
void dxball_crt_abort(void);
}

#endif
