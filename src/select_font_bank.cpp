extern "C" {
#include "allocator.h"
}
#include "resources.h"
extern "C" {
#include "rotation.h"
}

#include <stdlib.h>
#include <string.h>

/* FUNCTION: DXBALL 0x00403E90 */
void dxball_select_font_bank(DxBallInt bank)
{
    dxball_font_bank = bank;
    return;
}

