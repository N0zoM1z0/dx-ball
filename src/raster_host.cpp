#include "raster_host.h"
#include "raster_imports.h"
#include <stdlib.h>

#if defined(_WIN32)
/* A function address is a static initializer on the original VC4 linker. */
static DxBallInt DXBALL_RASTER_CALL host_muldiv(
    DxBallInt number, DxBallInt numerator, DxBallInt denominator)
{
    return MulDiv(number, numerator, denominator);
}
DxBallRasterOps dxball_raster_ops = { malloc, free, host_muldiv };
#else
/* Both spellings denote the same signed 64-bit arithmetic type. The legacy
   compiler predates C99's long-long spelling; no layout or body is selected. */
#if defined(_MSC_VER)
typedef __int64 RasterWideInt;
#else
typedef long long RasterWideInt;
#endif
typedef char RasterWideMustBe64Bits[(sizeof(RasterWideInt) == 8) ? 1 : -1];

static DxBallInt DXBALL_RASTER_CALL portable_muldiv(DxBallInt number, DxBallInt numerator,
                                DxBallInt denominator)
{
    RasterWideInt product, divisor, magnitude, result;
    if (denominator == 0) return -1;
    product = (RasterWideInt)number * numerator;
    divisor = denominator;
    if (divisor < 0) { product = -product; divisor = -divisor; }
    magnitude = product < 0 ? -product : product;
    result = (magnitude + divisor / 2) / divisor;
    if (product < 0) result = -result;
    if (result < (-2147483647 - 1) || result > 2147483647) return -1;
    return (DxBallInt)result;
}

DxBallRasterOps dxball_raster_ops = { malloc, free, portable_muldiv };

extern "C" DxBallInt DXBALL_RASTER_CALL MulDiv(
    DxBallInt number, DxBallInt numerator, DxBallInt denominator)
{
    return dxball_raster_ops.muldiv(number, numerator, denominator);
}
#endif
