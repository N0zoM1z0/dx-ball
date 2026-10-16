#include "runtime_x87_operation_tables.h"

extern const DxBallX87EntryAddress dxball_x87_pow_kernel;
extern const DxBallX87EntryAddress dxball_x87_pow_zero_exponent;
extern const DxBallX87EntryAddress dxball_x87_pow_dispatch_fallback;
extern const DxBallX87EntryAddress dxball_x87_pow_zero_base;
extern const DxBallX87EntryAddress dxball_x87_pow_both_zero;
extern const DxBallX87EntryAddress dxball_x87_top_nan_binary;
extern const DxBallX87EntryAddress dxball_x87_next_nan_binary;
extern const DxBallX87EntryAddress dxball_x87_nan_binary;
extern const DxBallX87EntryAddress dxball_x87_log10_kernel;
extern const DxBallX87EntryAddress dxball_x87_log_kernel;
extern const DxBallX87EntryAddress dxball_x87_log_zero;
extern const DxBallX87EntryAddress dxball_x87_log_infinite;
extern const DxBallX87EntryAddress dxball_x87_top_nan_unary;
extern const DxBallX87EntryAddress dxball_x87_exp_kernel;
extern const DxBallX87EntryAddress dxball_x87_exp_infinite;
extern const DxBallX87EntryAddress dxball_x87_return_one;

/* Complete records at 87tran.obj data +68; preceding constants are separate. */
DxBallX87BinaryOperation dxball_x87_pow_operation = {
    { 3, "pow", 0, 2, 29 },
    { &dxball_x87_pow_kernel, &dxball_x87_pow_zero_exponent,
      &dxball_x87_top_nan_binary, &dxball_x87_pow_dispatch_fallback,
      &dxball_x87_pow_zero_base, &dxball_x87_pow_both_zero,
      &dxball_x87_top_nan_binary, &dxball_x87_pow_dispatch_fallback,
      &dxball_x87_next_nan_binary, &dxball_x87_next_nan_binary,
      &dxball_x87_nan_binary, &dxball_x87_next_nan_binary,
      &dxball_x87_pow_dispatch_fallback, &dxball_x87_pow_dispatch_fallback,
      &dxball_x87_top_nan_binary, &dxball_x87_pow_dispatch_fallback }
};
DxBallX87UnaryOperation dxball_x87_log10_operation = {
    { 5, "log10", 0, 1, 27 },
    { &dxball_x87_log10_kernel, &dxball_x87_log_zero,
      &dxball_x87_top_nan_unary, &dxball_x87_log_infinite }
};
DxBallX87UnaryOperation dxball_x87_log_operation = {
    { 3, "log", 0, 1, 26 },
    { &dxball_x87_log_kernel, &dxball_x87_log_zero,
      &dxball_x87_top_nan_unary, &dxball_x87_log_infinite }
};
DxBallX87UnaryOperation dxball_x87_exp_operation = {
    { 3, "exp", 0, 1, 20 },
    { &dxball_x87_exp_kernel, &dxball_x87_return_one,
      &dxball_x87_top_nan_unary, &dxball_x87_exp_infinite }
};
