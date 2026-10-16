#include "runtime_x87_sqrt_table.h"

extern const DxBallX87EntryAddress dxball_x87_sqrt_kernel;
extern const DxBallX87EntryAddress dxball_x87_sqrt_zero;
extern const DxBallX87EntryAddress dxball_x87_top_nan_unary;
extern const DxBallX87EntryAddress dxball_x87_sqrt_infinite;

/* Complete 87sqrt.obj operation record at 0x004232E0. */
DxBallX87UnaryOperation dxball_x87_sqrt_operation = {
    { 4, "sqrt", 0, 1, 5 },
    { &dxball_x87_sqrt_kernel, &dxball_x87_sqrt_zero,
      &dxball_x87_top_nan_unary, &dxball_x87_sqrt_infinite }
};
