#ifndef DXBALL_RASTER_HOST_H
#define DXBALL_RASTER_HOST_H
#include "raster.h"

typedef struct DxBallRasterOps {
    void *(*allocate)(size_t bytes);
    void (*deallocate)(void *memory);
    DxBallInt (DXBALL_RASTER_CALL *muldiv)(DxBallInt number, DxBallInt numerator, DxBallInt denominator);
} DxBallRasterOps;

#ifdef __cplusplus
extern "C" {
#endif
extern DxBallRasterOps dxball_raster_ops;
#ifdef __cplusplus
}
#endif
#endif
