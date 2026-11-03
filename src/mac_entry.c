#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#include <sys/stat.h>

#include "mac_adapter.h"
#include "platform.h"
#include "allocator.h"

static int file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

static void setup_working_directory(void) {
    char exec_path[1024];
    uint32_t size = sizeof(exec_path);

    if (_NSGetExecutablePath(exec_path, &size) == 0) {
        // Resolve real path
        char real_path[1024];
        if (realpath(exec_path, real_path)) {
            // Check if we are inside a .app bundle (e.g. DX-Ball.app/Contents/MacOS/dxball)
            char *macos_dir = strstr(real_path, "/Contents/MacOS");
            if (macos_dir) {
                *macos_dir = '\0';
                char res_dir[1024];
                snprintf(res_dir, sizeof(res_dir), "%s/Contents/Resources", real_path);
                char test_file[1024];
                snprintf(test_file, sizeof(test_file), "%s/DEFAULT.BDS", res_dir);
                if (file_exists(test_file) || file_exists(res_dir)) {
                    chdir(res_dir);
                    printf("Running inside app bundle, switched to: %s\n", res_dir);
                    return;
                }
            }
        }
    }

    // Check local directories
    if (file_exists("original/DEFAULT.BDS") || file_exists("original/default.bds")) {
        chdir("original");
        printf("Switched working directory to ./original\n");
    } else if (file_exists("DEFAULT.BDS") || file_exists("default.bds")) {
        printf("Assets found in current directory.\n");
    } else {
        printf("Warning: DEFAULT.BDS not immediately found, searching in current dir.\n");
    }
}

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;

    setup_working_directory();

    printf("Step 1: initializing SDL...\n"); fflush(stdout);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    printf("Step 2: binding mac adapter...\n"); fflush(stdout);
    dxball_bind_mac();

    printf("Step 3: initializing runtime heap...\n"); fflush(stdout);
    dxball_initialize_runtime_heap();

    printf("Step 4: entering dxball_win_main...\n"); fflush(stdout);
    int exit_code = (int)dxball_win_main(0, 0, 0, 1);
    printf("dxball_win_main returned: %d\n", exit_code); fflush(stdout);

    SDL_Quit();
    return exit_code;
}
