#include "runtime_x87_operation_tables.h"

extern const DxBallX87EntryAddress dxball_x87_sin_kernel;
extern const DxBallX87EntryAddress dxball_x87_cos_kernel;
extern const DxBallX87EntryAddress dxball_x87_tan_kernel;
extern const DxBallX87EntryAddress dxball_x87_return_top;
extern const DxBallX87EntryAddress dxball_x87_return_one;
extern const DxBallX87EntryAddress dxball_x87_top_nan_unary;
extern const DxBallX87EntryAddress dxball_x87_indefinite_pop;

/* Complete records at 87trig.obj data +18; preceding constants are separate. */
DxBallX87UnaryOperation dxball_x87_sin_operation = {
    { 3, "sin", 0, 1, 30 },
    { &dxball_x87_sin_kernel, &dxball_x87_return_top,
      &dxball_x87_top_nan_unary, &dxball_x87_indefinite_pop }
};
DxBallX87UnaryOperation dxball_x87_cos_operation = {
    { 3, "cos", 0, 1, 18 },
    { &dxball_x87_cos_kernel, &dxball_x87_return_one,
      &dxball_x87_top_nan_unary, &dxball_x87_indefinite_pop }
};
DxBallX87UnaryOperation dxball_x87_tan_operation = {
    { 3, "tan", 0, 1, 32 },
    { &dxball_x87_tan_kernel, &dxball_x87_return_top,
      &dxball_x87_top_nan_unary, &dxball_x87_indefinite_pop }
};
