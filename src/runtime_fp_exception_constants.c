#include "runtime_fp_dispatch.h"

/* Complete util.obj initialized record, including indefinite and minus zero. */
DxBallDoubleConstant _d_inf = {{0x00000000U, 0x7ff00000U}};
DxBallDoubleConstant _d_ind = {{0x00000000U, 0xfff80000U}};
DxBallDoubleConstant _d_max = {{0xffffffffU, 0x7fefffffU}};
DxBallDoubleConstant _d_min = {{0x00000000U, 0x00100000U}};
DxBallDoubleConstant _d_mzero = {{0x00000000U, 0x80000000U}};
