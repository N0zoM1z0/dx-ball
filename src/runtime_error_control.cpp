#include "runtime_error_control.h"

/* FUNCTION: DXBALL 0x0041E250 */
int __crtMessageBoxA(const char *text, const char *caption, unsigned int flags)
{
    static DxBallCrtMessageBox message_box;
    static DxBallCrtActiveWindow active_window;
    static DxBallCrtLastPopup last_popup;
    void *parent = 0;
    if (message_box == 0) {
        void *module = LoadLibraryA("user32.dll");
        if (module == 0) goto failure;
        message_box = reinterpret_cast<DxBallCrtMessageBox>(GetProcAddress(module, "MessageBoxA"));
        if (message_box == 0) goto failure;
        active_window = reinterpret_cast<DxBallCrtActiveWindow>(GetProcAddress(module, "GetActiveWindow"));
        last_popup = reinterpret_cast<DxBallCrtLastPopup>(GetProcAddress(module, "GetLastActivePopup"));
    }
    if (active_window) parent = active_window();
    if (parent && last_popup) parent = last_popup(parent);
    return message_box(parent, text, caption, flags);
failure:
    return 0;
}

/* FUNCTION: DXBALL 0x0041E1D0 */
int _ValidateRead(const void *address, unsigned int bytes)
{
    int valid = 1;
    if (IsBadReadPtr(address, bytes)) valid = 0;
    return valid;
}

/* FUNCTION: DXBALL 0x0041E1F0 */
int _ValidateWrite(void *address, unsigned int bytes)
{
    int valid = 1;
    if (IsBadWritePtr(address, bytes)) valid = 0;
    return valid;
}

/* FUNCTION: DXBALL 0x0041E210 */
int _ValidateExecute(DxBallCrtProcedure address)
{
    int valid = 1;
    if (IsBadCodePtr(address)) valid = 0;
    return valid;
}

/* FUNCTION: DXBALL 0x0041E230 */
void dxball_crt_abort(void)
{
    dxball_crt_write_error(10);
    dxball_crt_raise(22);
    dxball_crt_quick_exit(3);
}
