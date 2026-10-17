#include <stdlib.h>
#include "list_initializers.h"

/* Canonical owners retain the recovered constructor order. Independently
   named board globals use ordered linker sections to preserve the observed
   neighboring bytes and terminal overlap. The layout type is metadata only. */
DxBallProjectileList dxball_projectiles;
DxBallBallList dxball_balls;
DxBallBallList dxball_duplicate_balls;
DxBallBrickEffectList dxball_brick_effects;
#if defined(__GNUC__)
#if defined(_WIN32)
#define DXBALL_BOARD_SLOT(N, T) __attribute__((section(".dxb$" N), aligned(__alignof__(T))))
#else
#define DXBALL_BOARD_SLOT(N, T) __attribute__((section(".dxb." N), aligned(__alignof__(T)), visibility("protected")))
#endif
#else
#define DXBALL_BOARD_SLOT(N, T)
#endif

extern "C" {
#if defined(_MSC_VER)
#pragma data_seg(".dxb$00")
#endif
DxBallByte dxball_board_storage[DXBALL_BOARD_COUNT][DXBALL_BOARD_SIZE] DXBALL_BOARD_SLOT("00", DxBallByte) = {0};
#if defined(_MSC_VER)
#pragma data_seg(".dxb$01")
#endif
DxBallUInt dxball_palette_tick DXBALL_BOARD_SLOT("01", DxBallUInt) = 0;
#if defined(_MSC_VER)
#pragma data_seg(".dxb$02")
#endif
DxBallByte dxball_unclassified_clock_tail[4] DXBALL_BOARD_SLOT("02", DxBallByte) = {0};
#if defined(_MSC_VER)
#pragma data_seg(".dxb$03")
#endif
#if defined(_MSC_VER)
__declspec(allocate(".dxb$03"))
#endif
DxBallExplosionList dxball_explosions DXBALL_BOARD_SLOT("03", DxBallExplosionList);
#if defined(_MSC_VER)
#pragma data_seg(".dxb$04")
#endif
DxBallInt dxball_ball_count DXBALL_BOARD_SLOT("04", DxBallInt) = 0;
#if defined(_MSC_VER)
#pragma data_seg(".dxb$05")
#endif
DxBallByte dxball_unclassified_count_tail[4] DXBALL_BOARD_SLOT("05", DxBallByte) = {0};
#if defined(_MSC_VER)
#pragma data_seg(".dxb$06")
#endif
DxBallByte dxball_board_tiles[DXBALL_BOARD_SIZE] DXBALL_BOARD_SLOT("06", DxBallByte) = {0};
#if defined(_MSC_VER)
#pragma data_seg()
#endif
}

#undef DXBALL_BOARD_SLOT

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



/* Typed list lifetimes retain ECX owners and ordinary C++ allocation. */
DxBallInt DXBALL_FASTCALL dxball_append_projectile(DxBallProjectileList *list)
{
    DxBallProjectileNode *node;
    node = new DxBallProjectileNode;
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) {
            list->last->next = node;
        } else {
            list->first = node;
        }
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_begin_projectiles(DxBallProjectileList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_projectile(DxBallProjectileList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_projectile(DxBallProjectileList *list)
{
    DxBallProjectileNode *node;
    if (list->current != NULL) {
        node = list->current;
        if (node->previous != NULL) {
            node->previous->next = node->next;
        }
        if (node->next != NULL) {
            node->next->previous = node->previous;
            list->current = node->next;
        } else {
            list->current = node->previous;
        }
        if (list->first == node) {
            list->first = node->next;
        }
        if (list->last == node) {
            list->last = node->previous;
        }
        delete node;
        return 1;
    } else {
        return 0;
    }
}

DxBallInt DXBALL_FASTCALL dxball_append_fire_effect(DxBallFireEffectList *list)
{
    DxBallFireEffectNode *node;
    node = new DxBallFireEffectNode;
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) {
            list->last->next = node;
        } else {
            list->first = node;
        }
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_begin_fire_effects(DxBallFireEffectList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_fire_effect(DxBallFireEffectList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_fire_effect(DxBallFireEffectList *list)
{
    DxBallFireEffectNode *node;
    if (list->current != NULL) {
        node = list->current;
        if (node->previous != NULL) {
            node->previous->next = node->next;
        }
        if (node->next != NULL) {
            node->next->previous = node->previous;
            list->current = node->next;
        } else {
            list->current = node->previous;
        }
        if (list->first == node) {
            list->first = node->next;
        }
        if (list->last == node) {
            list->last = node->previous;
        }
        delete node;
        return 1;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x004165D0 */
DxBallInt DXBALL_FASTCALL dxball_clear_projectile_list(DxBallProjectileList *list)
{
    while (dxball_remove_projectile(list)) {
    }
    return 1;
}

/* FUNCTION: DXBALL 0x00416510 */
DxBallInt DXBALL_FASTCALL dxball_clear_fire_effect_list(DxBallFireEffectList *list)
{
    while (dxball_remove_fire_effect(list)) {
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_append_explosion(DxBallExplosionList *list)
{
    DxBallExplosionNode *node;
    node = new DxBallExplosionNode;
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) {
            list->last->next = node;
        } else {
            list->first = node;
        }
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_begin_explosions(DxBallExplosionList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_explosion(DxBallExplosionList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_explosion(DxBallExplosionList *list)
{
    DxBallExplosionNode *node;
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
        delete node;
        return 1;
    } else {
        return 0;
    }
}

DxBallInt DXBALL_FASTCALL dxball_clear_explosion_list(DxBallExplosionList *list)
{
    while (dxball_remove_explosion(list)) {
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_append_ball(DxBallBallList *list)
{
    DxBallBallNode *node;
    node = new DxBallBallNode;
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

DxBallInt DXBALL_FASTCALL dxball_begin_balls(DxBallBallList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_ball(DxBallBallList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_ball(DxBallBallList *list)
{
    DxBallBallNode *node;
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
        delete node;
        return 1;
    } else {
        return 0;
    }
}

DxBallInt DXBALL_FASTCALL dxball_clear_ball_list(DxBallBallList *list)
{
    while (dxball_remove_ball(list)) {
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_append_brick_effect(DxBallBrickEffectList *list)
{
    DxBallBrickEffectNode *node;
    node = new DxBallBrickEffectNode;
    if (node != NULL) {
        node->previous = list->last;
        node->next = NULL;
        if (list->last != NULL) {
            list->last->next = node;
        } else {
            list->first = node;
        }
        list->last = node;
        list->current = list->last;
    } else {
        exit(1);
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_begin_brick_effects(DxBallBrickEffectList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_brick_effect(DxBallBrickEffectList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_brick_effect(DxBallBrickEffectList *list)
{
    DxBallBrickEffectNode *node;
    if (list->current != NULL) {
        node = list->current;
        if (node->previous != NULL) {
            node->previous->next = node->next;
        }
        if (node->next != NULL) {
            node->next->previous = node->previous;
            list->current = node->next;
        } else {
            list->current = node->previous;
        }
        if (list->first == node) {
            list->first = node->next;
        }
        if (list->last == node) {
            list->last = node->previous;
        }
        delete node;
        return 1;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x004165A0 */
DxBallInt DXBALL_FASTCALL dxball_clear_brick_effect_list(DxBallBrickEffectList *list)
{
    while (dxball_remove_brick_effect(list)) {
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_append_bonus(DxBallBonusList *list)
{
    DxBallBonusNode *node;
    node = new DxBallBonusNode;
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

DxBallInt DXBALL_FASTCALL dxball_begin_bonuses(DxBallBonusList *list)
{
    list->current = list->first;
    return list->current != NULL;
}

DxBallInt DXBALL_FASTCALL dxball_advance_bonus(DxBallBonusList *list)
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

DxBallInt DXBALL_FASTCALL dxball_remove_bonus(DxBallBonusList *list)
{
    DxBallBonusNode *node;
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
        delete node;
        return 1;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x00416570 */
DxBallInt DXBALL_FASTCALL dxball_clear_bonus_list(DxBallBonusList *list)
{
    while (dxball_remove_bonus(list)) {
    }
    return 1;
}

DxBallInt DXBALL_FASTCALL dxball_append_particle(DxBallParticleList *list)
{
    DxBallParticleNode *node;
    node = new DxBallParticleNode;
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
        delete node;
        return 1;
    } else {
        return 0;
    }
}

/* FUNCTION: DXBALL 0x00416540 */
DxBallInt DXBALL_FASTCALL dxball_clear_particle_list(DxBallParticleList *list)
{
    while (dxball_remove_particle(list)) {
    }
    return 1;
}
