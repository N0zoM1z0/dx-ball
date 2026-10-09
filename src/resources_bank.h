#ifndef DXBALL_RESOURCES_BANK_H
#define DXBALL_RESOURCES_BANK_H
#include "resources.h"

/* Whole-bank lifecycle API; valid banks are 0..2. Releases all 255 owned
   slots, including zero, resets metadata, writes a single-space filename,
   and restores the previously selected bank. */
void dxball_release_sprite_bank(DxBallInt bank);
#endif
