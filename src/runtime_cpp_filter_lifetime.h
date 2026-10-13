#ifndef DXBALL_RUNTIME_CPP_FILTER_LIFETIME_H
#define DXBALL_RUNTIME_CPP_FILTER_LIFETIME_H
#include "runtime_cpp_filter.h"
#include "runtime_onexit.h"

#ifdef __cplusplus
extern "C" {
#endif
void dxball_cpp_install_unhandled_filter(void);
void dxball_cpp_filter_initializer(void);
extern DxBallCrtCallback dxball_cpp_filter_initialization_entry;
#ifdef __cplusplus
}
#endif
#endif
