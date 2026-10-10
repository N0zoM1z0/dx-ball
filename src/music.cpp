extern "C" {
#include "allocator.h"
#include "midi.h"
}

DxBallMusic *dxball_music;

void *DxBallMusic::operator new(size_t bytes)
{
    return dxball_new_bytes(bytes);
}

void DxBallMusic::operator delete(void *memory)
{
    dxball_runtime_delete(memory);
}

/* FUNCTION: DXBALL 0x00401B90 */
DxBallInt dxball_load_music(const char *path, DxBallInt play)
{
    if (dxball_music != NULL) dxball_close_music();
    dxball_music = new DxBallMusic;
    if (dxball_open_mds(&dxball_music->context, path, 0, 1) != 0) {
        delete dxball_music;
        dxball_music = NULL;
        return 0;
    }
    dxball_music->playing = 0;
    if (play != 0) {
        if (dxball_play_mds(dxball_music->context, 1) != 0) {
            dxball_release_mds(dxball_music->context);
            delete dxball_music;
            dxball_music = NULL;
            return 0;
        }
        dxball_music->playing = 1;
    }
    return 1;
}

/* FUNCTION: DXBALL 0x00401C90 */
void dxball_resume_music(void)
{
    if (dxball_music == NULL) return;
    if (dxball_play_mds(dxball_music->context, 1) != 0) return;
    dxball_music->playing = 1;
    return;
}

/* FUNCTION: DXBALL 0x00401CE0 */
void dxball_pause_music(void)
{
    if (dxball_music == NULL) return;
    if (dxball_pause_mds(dxball_music->context) != 0) return;
    dxball_music->playing = 0;
    return;
}

/* FUNCTION: DXBALL 0x00401D30 */
void dxball_restart_music(void)
{
    if (dxball_music == NULL) return;
    if (dxball_stop_mds(dxball_music->context) != 0) return;
    if (dxball_play_mds(dxball_music->context, 1) != 0) return;
    dxball_music->playing = 1;
    return;
}

/* FUNCTION: DXBALL 0x00401DA0 */
void dxball_close_music(void)
{
    if (dxball_music == NULL) return;
    dxball_stop_mds(dxball_music->context);
    dxball_release_mds(dxball_music->context);
    delete dxball_music;
    dxball_music = NULL;
    return;
}
