#include "runtime_fdiv_processors.h"

int dxball_crt_test_fdiv_processors(void)
{
    if (_ms_p5_test_fdiv())
        return 1;
    void *module = LoadLibraryA("KERNEL32");
    if (!module)
        return 0;
    DxBallFdivGetAffinity get_affinity = (DxBallFdivGetAffinity)(void (*)(void))
        GetProcAddress(module, "GetProcessAffinityMask");
    if (!get_affinity)
        return 0;
    DxBallFdivGetHandle get_process = (DxBallFdivGetHandle)(void (*)(void))
        GetProcAddress(module, "GetCurrentProcess");
    if (!get_process)
        return 0;
    DxBallFdivSetAffinity set_affinity = (DxBallFdivSetAffinity)(void (*)(void))
        GetProcAddress(module, "SetThreadAffinityMask");
    if (!set_affinity)
        return 0;
    DxBallFdivGetHandle get_thread = (DxBallFdivGetHandle)(void (*)(void))
        GetProcAddress(module, "GetCurrentThread");
    if (!get_thread)
        return 0;
    size_t process_mask, system_mask;
    void *process = get_process();
    if (!get_affinity(process, &process_mask, &system_mask))
        return 0;
    for (int bit = 0; bit < 32; ++bit) {
        size_t selected = (size_t)1 << bit;
        if (system_mask & selected) {
            set_affinity(get_thread(), selected);
            if (_ms_p5_test_fdiv()) {
                set_affinity(get_thread(), system_mask);
                return 1;
            }
        }
    }
    set_affinity(get_thread(), system_mask);
    return 0;
}
