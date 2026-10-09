#ifndef DXBALL_PARTICLES_H
#define DXBALL_PARTICLES_H

#include "gameplay.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DxBallParticleNode {
    DxBallInt x, y, dx, dy, gravity, gravity_ticks, color, fade_steps, fade_ticks;
    struct DxBallParticleNode *next, *previous;
} DxBallParticleNode;

typedef struct DxBallParticleList {
    DxBallParticleNode *current, *first, *last;
} DxBallParticleList;

extern DxBallParticleList dxball_particles;
/* Region dependency at 0x408990; not an implementation of the display backend. */
extern void (*dxball_particle_region)(DxBallInt left, DxBallInt top,
                                     DxBallInt right, DxBallInt bottom);

DxBallInt DXBALL_FASTCALL dxball_append_particle(DxBallParticleList *list);
DxBallInt DXBALL_FASTCALL dxball_begin_particles(DxBallParticleList *list);
DxBallInt DXBALL_FASTCALL dxball_advance_particle(DxBallParticleList *list);
DxBallInt DXBALL_FASTCALL dxball_remove_particle(DxBallParticleList *list);
DxBallInt DXBALL_FASTCALL dxball_clear_particle_list(DxBallParticleList *list);
void dxball_spawn_particle(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy,
                           DxBallInt color, DxBallInt gravity);
void dxball_update_particles(void);
/* Requires a writable 8-bit effect surface with space for each 2x2 particle. */
void dxball_draw_particles(void);

#ifdef __cplusplus
}
#endif

#endif
