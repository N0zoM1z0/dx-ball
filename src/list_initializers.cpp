#include "list_initializers.h"

/* Canonical owners, in the recovered constructor-wrapper order. The board
   storage remains one aggregate: its real explosion member owns the +0xC
   observation word also visible to the terminal bank-copy operation. */
DxBallProjectileList dxball_projectiles;
DxBallBallList dxball_balls;
DxBallBallList dxball_duplicate_balls;
DxBallBrickEffectList dxball_brick_effects;
DxBallBoardStorage dxball_board_storage;
DxBallExplosionList dxball_explosive_sources;
DxBallBonusList dxball_bonuses;
DxBallParticleList dxball_particles;
DxBallFireEffectList dxball_fire_effects;

/* FUNCTION: DXBALL 0x0040F200 */
DxBallProjectileList::DxBallProjectileList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040F260 */
DxBallBallList::DxBallBallList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040F2E0 */
DxBallBrickEffectList::DxBallBrickEffectList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040F340 */
DxBallExplosionList::DxBallExplosionList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040F3C0 */
DxBallBonusList::DxBallBonusList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040F420 */
DxBallParticleList::DxBallParticleList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

/* FUNCTION: DXBALL 0x0040F480 */
DxBallFireEffectList::DxBallFireEffectList()
{
    current = 0;
    first = 0;
    last = 0;
    unclassified_0c = 0;
    return;
}

