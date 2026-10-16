#include "runtime_x87_operation_tables.h"

/* Genuine remaining machine entries, represented without a fictitious C ABI. */
extern const DxBallX87EntryAddress dxball_x87_asin_kernel;
extern const DxBallX87EntryAddress dxball_x87_acos_kernel;
extern const DxBallX87EntryAddress dxball_x87_atan_kernel;
extern const DxBallX87EntryAddress dxball_x87_atan2_kernel;
extern const DxBallX87EntryAddress dxball_x87_half_pi;
extern const DxBallX87EntryAddress dxball_x87_atan_infinite;
extern const DxBallX87EntryAddress dxball_x87_atan2_zero_divisor;
extern const DxBallX87EntryAddress dxball_x87_atan2_zero;
extern const DxBallX87EntryAddress dxball_x87_atan2_both_zero;
extern const DxBallX87EntryAddress dxball_x87_return_top;
extern const DxBallX87EntryAddress dxball_x87_top_nan_unary;
extern const DxBallX87EntryAddress dxball_x87_indefinite_pop;
extern const DxBallX87EntryAddress dxball_x87_top_nan_binary;
extern const DxBallX87EntryAddress dxball_x87_next_nan_binary;
extern const DxBallX87EntryAddress dxball_x87_nan_binary;
extern const DxBallX87EntryAddress dxball_x87_indefinite;

/* Writable original 87triga.obj descriptors at 0x00423230..0x004232DF. */
DxBallX87UnaryOperation dxball_x87_asin_operation = {
    { 4, "asin", 0, 1, 14 },
    { &dxball_x87_asin_kernel, &dxball_x87_return_top,
      &dxball_x87_top_nan_unary, &dxball_x87_indefinite_pop }
};
DxBallX87UnaryOperation dxball_x87_acos_operation = {
    { 4, "acos", 0, 1, 13 },
    { &dxball_x87_acos_kernel, &dxball_x87_half_pi,
      &dxball_x87_top_nan_unary, &dxball_x87_indefinite_pop }
};
DxBallX87UnaryOperation dxball_x87_atan_operation = {
    { 4, "atan", 0, 1, 15 },
    { &dxball_x87_atan_kernel, &dxball_x87_return_top,
      &dxball_x87_top_nan_unary, &dxball_x87_atan_infinite }
};
DxBallX87BinaryOperation dxball_x87_atan2_operation = {
    { 5, "atan2", 0, 2, 16 },
    { &dxball_x87_atan2_kernel, &dxball_x87_atan2_zero_divisor,
      &dxball_x87_top_nan_binary, &dxball_x87_atan2_zero,
      &dxball_x87_atan2_zero, &dxball_x87_atan2_both_zero,
      &dxball_x87_top_nan_binary, &dxball_x87_atan2_zero,
      &dxball_x87_next_nan_binary, &dxball_x87_next_nan_binary,
      &dxball_x87_nan_binary, &dxball_x87_next_nan_binary,
      &dxball_x87_atan2_zero_divisor, &dxball_x87_atan2_zero_divisor,
      &dxball_x87_top_nan_binary, &dxball_x87_indefinite }
};
