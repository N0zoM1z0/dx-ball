#ifndef DXBALL_RASTER_IMPORTS_H
#define DXBALL_RASTER_IMPORTS_H
#include "raster.h"

#ifdef __cplusplus
extern "C" {
#endif
#if defined(_WIN32)
__declspec(dllimport) DxBallInt DXBALL_RASTER_CALL MulDiv(
    DxBallInt number, DxBallInt numerator, DxBallInt denominator);
#else
DxBallInt DXBALL_RASTER_CALL MulDiv(
    DxBallInt number, DxBallInt numerator, DxBallInt denominator);
#endif
#ifdef __cplusplus
}
#endif
#endif
