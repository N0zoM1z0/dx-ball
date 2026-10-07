/* Independent SDK surfaces, never a call into the game or its address space. */
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <ddraw.h>
#include <stdio.h>
#include <string.h>

static LPDIRECTDRAW draw;
static LPDIRECTDRAWSURFACE primary, secondary, board;
static int ready, inactive_seen, resume_pending;

static HRESULT lock_once(LPDIRECTDRAWSURFACE surface)
{
    DDSURFACEDESC description;
    HRESULT result;
    memset(&description, 0, sizeof(description));
    description.dwSize = sizeof(description);
    result = IDirectDrawSurface_Lock(surface, NULL, &description, 0, NULL);
    if (SUCCEEDED(result)) IDirectDrawSurface_Unlock(surface, description.lpSurface);
    return result;
}

static void snapshot(const char *phase)
{
    HRESULT before, lost, after, back_lost, back_lock, board_lost, board_lock;
    before = IDirectDrawSurface_GetBltStatus(primary, DDGBS_CANBLT);
    lost = IDirectDrawSurface_IsLost(primary);
    after = IDirectDrawSurface_GetBltStatus(primary, DDGBS_CANBLT);
    back_lost = IDirectDrawSurface_IsLost(secondary);
    back_lock = lock_once(secondary);
    board_lost = IDirectDrawSurface_IsLost(board);
    board_lock = lock_once(board);
    printf("{\"phase\":\"%s\",\"primary_blt_before\":\"0x%08lx\","
           "\"primary_is_lost\":\"0x%08lx\",\"primary_blt_after\":\"0x%08lx\","
           "\"back_is_lost\":\"0x%08lx\",\"back_lock\":\"0x%08lx\","
           "\"board_is_lost\":\"0x%08lx\",\"board_lock\":\"0x%08lx\"}\n",
           phase, (unsigned long)before, (unsigned long)lost, (unsigned long)after,
           (unsigned long)back_lost, (unsigned long)back_lock,
           (unsigned long)board_lost, (unsigned long)board_lock);
    fflush(stdout);
}

static LRESULT CALLBACK probe_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_ACTIVATEAPP && ready) {
        if (!wparam) {
            inactive_seen = 1;
            ShowWindow(window, SW_MINIMIZE);
            printf("{\"phase\":\"inactive\"}\n"); fflush(stdout);
        } else if (inactive_seen) resume_pending = 1;
    }
    if (message == WM_TIMER && resume_pending) {
        HRESULT primary_restore, board_restore;
        resume_pending = 0;
        snapshot("focus-return");
        primary_restore = IDirectDrawSurface_Restore(primary);
        board_restore = IDirectDrawSurface_Restore(board);
        printf("{\"phase\":\"explicit-own-restore\",\"primary\":\"0x%08lx\","
               "\"board\":\"0x%08lx\"}\n", (unsigned long)primary_restore,
               (unsigned long)board_restore);
        fflush(stdout);
        snapshot("after-own-restore");
        ready = 0;
        PostMessageA(window, WM_CLOSE, 0, 0);
    }
    if (message == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProcA(window, message, wparam, lparam);
}

static int setup(HWND window)
{
    DDSURFACEDESC description;
    DDSCAPS caps;
    HRESULT result;
    result = DirectDrawCreate(NULL, &draw, NULL);
    if (FAILED(result)) return 10;
    result = IDirectDraw_SetCooperativeLevel(draw, window, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (FAILED(result)) return 11;
    result = IDirectDraw_SetDisplayMode(draw, 640, 480, 8);
    if (FAILED(result)) return 12;
    memset(&description, 0, sizeof(description));
    description.dwSize = sizeof(description);
    description.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    description.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    description.dwBackBufferCount = 1;
    result = IDirectDraw_CreateSurface(draw, &description, &primary, NULL);
    if (FAILED(result)) return 13;
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    result = IDirectDrawSurface_GetAttachedSurface(primary, &caps, &secondary);
    if (FAILED(result)) return 14;
    memset(&description, 0, sizeof(description));
    description.dwSize = sizeof(description);
    description.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    description.dwWidth = 640; description.dwHeight = 480;
    /* Original working-surface request specifies OFFSCREENPLAIN only. */
    description.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    result = IDirectDraw_CreateSurface(draw, &description, &board, NULL);
    if (FAILED(result)) return 15;
    return 0;
}

int main(void)
{
    WNDCLASSA record;
    HWND window;
    MSG message;
    int code;
    if (sizeof(void *) != 4 || sizeof(DDSURFACEDESC) != 108) return 2;
    memset(&record, 0, sizeof(record));
    record.lpfnWndProc = probe_proc;
    record.hInstance = GetModuleHandleA(NULL);
    /* Match the peer's discovery contract; no game runs in this SDK scenario. */
    record.lpszClassName = "DX-Ball";
    if (!RegisterClassA(&record)) return 3;
    window = CreateWindowA(record.lpszClassName, "DX-Ball", WS_POPUP,
                           0, 0, 640, 480, NULL, NULL, record.hInstance, NULL);
    if (window == NULL) return 4;
    ShowWindow(window, SW_SHOW); SetForegroundWindow(window);
    code = setup(window);
    if (code == 0) {
        snapshot("ready");
        ready = 1;
        SetTimer(window, 1, 100, NULL);
        while (GetMessageA(&message, NULL, 0, 0) > 0) {
            TranslateMessage(&message); DispatchMessageA(&message);
        }
        KillTimer(window, 1);
    } else fprintf(stderr, "DirectDraw loss probe setup failed at step %d\n", code);
    if (secondary != NULL) IDirectDrawSurface_Release(secondary);
    if (board != NULL) IDirectDrawSurface_Release(board);
    if (primary != NULL) IDirectDrawSurface_Release(primary);
    if (draw != NULL) {
        IDirectDraw_RestoreDisplayMode(draw);
        IDirectDraw_SetCooperativeLevel(draw, NULL, DDSCL_NORMAL);
        IDirectDraw_Release(draw);
    }
    return code;
}
