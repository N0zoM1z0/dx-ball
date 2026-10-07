#include "particles.h"
#include "effects.h"
#include "resources.h"

#include <stdlib.h>
#include <string.h>

DxBallParticleList dxball_particles;
void (*dxball_particle_region)(DxBallInt, DxBallInt, DxBallInt, DxBallInt);

DxBallInt DXBALL_FASTCALL dxball_append_particle(DxBallParticleList *list)
{
    DxBallParticleNode *node;
    node = (DxBallParticleNode *)dxball_allocate_node(sizeof(DxBallParticleNode));
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) list->last->next = node;
        else list->first = node;
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_begin_particles(DxBallParticleList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_particle(DxBallParticleList *list)
{
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current == NULL) {
            list->current = list->first;
            return 0;
        }
        return 1;
    }
    return 0;
}

DxBallInt DXBALL_FASTCALL dxball_remove_particle(DxBallParticleList *list)
{
    DxBallParticleNode *node;
    if (list->current != NULL) {
        node = list->current;
        if (node->previous != NULL) node->previous->next = node->next;
        if (node->next != NULL) {
            node->next->previous = node->previous;
            list->current = node->next;
        } else {
            list->current = node->previous;
        }
        if (list->first == node) list->first = node->next;
        if (list->last == node) list->last = node->previous;
        dxball_deallocate_node(node);
        return 1;
    } else {
        return 0;
    }
}

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
    DxBallSurfaceDesc description;
    DxBallDDSurface *surface;
    DxBallByte *pixels;
    DxBallInt result;
    if (dxball_begin_particles(&dxball_particles)) {
        surface = (DxBallDDSurface *)dxball_effect_surface;
        description.size = sizeof(description);
        description.flags = 0xE;
        surface->vtable->get_desc(surface, &description);
        do {
            result = surface->vtable->lock(surface, NULL, &description, 0, NULL);
        } while (result != 0);
        do {
            pixels = description.pixels + dxball_particles.current->y * description.pitch +
                     dxball_particles.current->x;
            memset(pixels, dxball_particles.current->color, 2);
            memset(pixels + description.pitch, dxball_particles.current->color, 2);
            dxball_particle_region(dxball_particles.current->x, dxball_particles.current->y,
                                    dxball_particles.current->x + 2, dxball_particles.current->y + 2);
        } while (dxball_advance_particle(&dxball_particles));
        surface->vtable->unlock(surface, NULL);
    }
    return;
}
