#include "runtime_float_format.h"

/* Actual cmiscdat defaults, retained without incompatible callback casts. */
DxBallCrtFloatCallbacks _cfltcvt_tab = {
    {dxball_crt_float_unavailable}, {dxball_crt_float_unavailable},
    {dxball_crt_float_unavailable}, {dxball_crt_float_unavailable},
    {dxball_crt_float_unavailable}, {dxball_crt_float_unavailable}
};
