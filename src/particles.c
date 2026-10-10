#include "particles.h"
#include "allocator.h"
#include "effects.h"
#include "resources.h"
#include "display.h"

#include <stdlib.h>
#include <string.h>

static void queue_particle_bounds(DxBallInt left, DxBallInt top, DxBallInt right, DxBallInt bottom)
{
    DxBallRect rect;
    rect.left = left;
    rect.top = top;
    rect.right = right;
    rect.bottom = bottom;
    dxball_queue_region(rect);
}

void (*dxball_particle_region)(DxBallInt, DxBallInt, DxBallInt, DxBallInt) = queue_particle_bounds;

void dxball_spawn_particle(DxBallInt x, DxBallInt y, DxBallInt dx, DxBallInt dy,
                           DxBallInt color, DxBallInt gravity)
{
    if (x > 20 && x < 619 && y > 0 && y < 479) {
        dxball_append_particle(&dxball_particles);
        dxball_particles.current->x = x;
        dxball_particles.current->y = y;
        dxball_particles.current->dx = dx;
        dxball_particles.current->dy = dy;
        dxball_particles.current->color = color;
        dxball_particles.current->fade_steps = 0;
        dxball_particles.current->fade_ticks = 0;
        dxball_particles.current->gravity = gravity;
        dxball_particles.current->gravity_ticks = 0;
    }
    return;
}

void dxball_update_particles(void)
{
    if (dxball_begin_particles(&dxball_particles)) {
        do {
            dxball_particles.current->x += dxball_particles.current->dx;
            dxball_particles.current->y += dxball_particles.current->dy;
            if (dxball_particles.current->gravity == 1) {
                ++dxball_particles.current->gravity_ticks;
                if (dxball_particles.current->gravity_ticks > 5) {
                    ++dxball_particles.current->dy;
                    dxball_particles.current->gravity_ticks = 0;
                }
            }
            if (dxball_particles.current->x < 20 || dxball_particles.current->x > 618 ||
                    dxball_particles.current->y < 0 || dxball_particles.current->y > 478) {
                dxball_remove_particle(&dxball_particles);
            } else {
                ++dxball_particles.current->fade_ticks;
                if (dxball_particles.current->fade_ticks > 4) {
                    dxball_particles.current->fade_ticks = 0;
                    ++dxball_particles.current->color;
                    ++dxball_particles.current->fade_steps;
                    if (dxball_particles.current->fade_steps > 6) {
                        dxball_remove_particle(&dxball_particles);
                    }
                }
            }
        } while (dxball_advance_particle(&dxball_particles));
    }
    return;
}

void dxball_draw_particles(void)
{
    DxBallRect rect;
    DxBallSurfaceDesc description;
    DxBallInt result;
    DxBallByte *pixels;
    if (dxball_begin_particles(&dxball_particles)) {
        description.size = sizeof(description);
        description.flags = 0xE;
        ((DxBallDDSurface *)dxball_effect_surface)->vtable->get_desc(
            (DxBallDDSurface *)dxball_effect_surface, &description);
        do {
            result = ((DxBallDDSurface *)dxball_effect_surface)->vtable->lock(
                (DxBallDDSurface *)dxball_effect_surface, NULL, &description, 0, NULL);
        } while (result != 0);
        do {
            pixels = description.pixels;
            pixels += dxball_particles.current->y * description.pitch +
                      dxball_particles.current->x;
            memset(pixels, dxball_particles.current->color, 2);
            pixels += description.pitch;
            memset(pixels, dxball_particles.current->color, 2);
            rect.top = dxball_particles.current->y;
            rect.bottom = dxball_particles.current->y + 2;
            rect.left = dxball_particles.current->x;
            rect.right = dxball_particles.current->x + 2;
            dxball_queue_region(rect);
        } while (dxball_advance_particle(&dxball_particles));
        ((DxBallDDSurface *)dxball_effect_surface)->vtable->unlock(
            (DxBallDDSurface *)dxball_effect_surface, NULL);
    }
    return;
}
