#include <stdlib.h>
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



/* Typed projectile/fire lifetimes retain ECX owners and ordinary C++ allocation. */
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
    if (list->current != NULL) {
        return 1;
    } else {
        return 0;
    }
}

DxBallInt DXBALL_FASTCALL dxball_advance_projectile(DxBallProjectileList *list)
{
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current == NULL) {
            list->current = list->first;
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
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
    if (list->current != NULL) {
        return 1;
    } else {
        return 0;
    }
}

DxBallInt DXBALL_FASTCALL dxball_advance_fire_effect(DxBallFireEffectList *list)
{
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current == NULL) {
            list->current = list->first;
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
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
