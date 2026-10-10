#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "windows_adapter.h"
#include "sound.h"
#include "midi.h"
#include "paddle.h"
#include "raster.h"
#include "bitmap.h"
#include "allocator.h"

typedef char WindowsAdapterRequiresI686[(sizeof(void *) == 4) ? 1 : -1];
typedef char WindowsMessageLayout[(sizeof(MSG) == sizeof(DxBallMessage)) ? 1 : -1];
typedef char WindowsMidiLayout[(sizeof(MIDIHDR) == sizeof(DxBallMidiHeader)) ? 1 : -1];
typedef DxBallInt (DXBALL_DDCALL *DrawFactory)(void *, DxBallDDraw **, void *);
typedef DxBallInt (DXBALL_DDCALL *SoundFactory)(void *, DxBallSoundDevice **, void *);
static DrawFactory draw_factory;
static SoundFactory sound_factory;
static HMODULE draw_module, sound_module;
static DxBallWindowProc registered_procedure;
static DxBallMidiCallback stream_callback;

static LRESULT CALLBACK window_callback(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    return (LRESULT)registered_procedure((DxBallHandle)window, message,
        (DxBallHandle)wparam, (DxBallWindowResult)lparam);
}

static void CALLBACK midi_callback(HMIDIOUT stream, UINT message, DWORD instance,
                                  DWORD parameter1, DWORD parameter2)
{
    stream_callback((DxBallMidiHandle)stream, message, instance,
        (DxBallMidiHeader *)parameter1, parameter2);
}

static DxBallHandle DXBALL_DDCALL load_icon(DxBallHandle instance, DxBallHandle name)
{ return (DxBallHandle)LoadIconA((HINSTANCE)instance, (LPCSTR)name); }
static DxBallHandle DXBALL_DDCALL load_cursor(DxBallHandle instance, DxBallHandle name)
{ return (DxBallHandle)LoadCursorA((HINSTANCE)instance, (LPCSTR)name); }
static DxBallHandle DXBALL_DDCALL stock_object(DxBallInt object)
{ return (DxBallHandle)GetStockObject(object); }
static DxBallUInt DXBALL_DDCALL register_class(const DxBallWindowClass *input)
{
    WNDCLASSA record;
    registered_procedure = input->procedure;
    record.style = input->style; record.lpfnWndProc = window_callback;
    record.cbClsExtra = input->class_extra; record.cbWndExtra = input->window_extra;
    record.hInstance = (HINSTANCE)input->instance; record.hIcon = (HICON)input->icon;
    record.hCursor = (HCURSOR)input->cursor; record.hbrBackground = (HBRUSH)input->background;
    record.lpszMenuName = input->menu; record.lpszClassName = input->name;
    return RegisterClassA(&record);
}
static DxBallHandle DXBALL_DDCALL create_window(DxBallUInt extended, const char *class_name,
    const char *title, DxBallUInt style, DxBallInt x, DxBallInt y, DxBallInt width,
    DxBallInt height, DxBallHandle parent, DxBallHandle menu, DxBallHandle instance, void *parameter)
{
    return (DxBallHandle)CreateWindowExA(extended, class_name, title, style, x, y,
        width, height, (HWND)parent, (HMENU)menu, (HINSTANCE)instance, parameter);
}
static DxBallInt DXBALL_DDCALL show_window(DxBallHandle window, DxBallInt show)
{ return ShowWindow((HWND)window, show); }
static DxBallInt DXBALL_DDCALL update_window(DxBallHandle window)
{ return UpdateWindow((HWND)window); }
static DxBallHandle DXBALL_DDCALL set_focus(DxBallHandle window)
{ return (DxBallHandle)SetFocus((HWND)window); }
static DxBallInt DXBALL_DDCALL destroy_window(DxBallHandle window)
{ return DestroyWindow((HWND)window); }
static DxBallInt DXBALL_DDCALL message_box(DxBallHandle window, const char *message,
                                        const char *title, DxBallUInt flags)
{ return MessageBoxA((HWND)window, message, title, flags); }
static DxBallInt DXBALL_DDCALL create_draw(void *guid, DxBallDDraw **device, void *outer)
{
    if (draw_factory == NULL) return (DxBallInt)0x80004005UL;
    return draw_factory(guid, device, outer);
}
static DxBallInt DXBALL_DDCALL create_sound(void *guid, DxBallSoundDevice **device, void *outer)
{
    if (sound_factory == NULL) return (DxBallInt)0x88780078UL;
    return sound_factory(guid, device, outer);
}
static DxBallInt DXBALL_DDCALL cursor_position(DxBallPoint *point)
{
    POINT sdk; BOOL result;
    memcpy(&sdk, point, sizeof(sdk)); result = GetCursorPos(&sdk);
    point->x = sdk.x; point->y = sdk.y;
    return result;
}
static DxBallInt DXBALL_DDCALL peek_message(DxBallMessage *message, DxBallHandle window,
    DxBallUInt first, DxBallUInt last, DxBallUInt remove)
{
    MSG sdk; BOOL result;
    memcpy(&sdk, message, sizeof(sdk));
    result = PeekMessageA(&sdk, (HWND)window, first, last, remove);
    memcpy(message, &sdk, sizeof(sdk)); return result;
}
static DxBallInt DXBALL_DDCALL wait_message(void) { return WaitMessage(); }
static DxBallInt DXBALL_DDCALL get_message(DxBallMessage *message, DxBallHandle window,
    DxBallUInt first, DxBallUInt last)
{
    MSG sdk; BOOL result;
    memcpy(&sdk, message, sizeof(sdk)); result = GetMessageA(&sdk, (HWND)window, first, last);
    memcpy(message, &sdk, sizeof(sdk)); return result;
}
static DxBallInt DXBALL_DDCALL translate_message(const DxBallMessage *message)
{ MSG sdk; memcpy(&sdk, message, sizeof(sdk)); return TranslateMessage(&sdk); }
static DxBallWindowResult DXBALL_DDCALL dispatch_message(const DxBallMessage *message)
{ MSG sdk; memcpy(&sdk, message, sizeof(sdk)); return DispatchMessageA(&sdk); }
static DxBallWindowResult DXBALL_DDCALL default_proc(DxBallHandle window, DxBallUInt message,
    DxBallHandle wparam, DxBallWindowResult lparam)
{ return DefWindowProcA((HWND)window, message, (WPARAM)wparam, (LPARAM)lparam); }
static DxBallInt DXBALL_DDCALL post_message(DxBallHandle window, DxBallUInt message,
    DxBallHandle wparam, DxBallWindowResult lparam)
{ return PostMessageA((HWND)window, message, (WPARAM)wparam, (LPARAM)lparam); }
static void DXBALL_DDCALL post_quit(DxBallInt code) { PostQuitMessage(code); }
static DxBallHandle DXBALL_DDCALL set_cursor(DxBallHandle cursor)
{ return (DxBallHandle)SetCursor((HCURSOR)cursor); }
static DxBallHandle DXBALL_DDCALL set_capture(DxBallHandle window)
{ return (DxBallHandle)SetCapture((HWND)window); }
static DxBallInt DXBALL_DDCALL release_capture(void) { return ReleaseCapture(); }
static DxBallHandle DXBALL_DDCALL open_semaphore(DxBallUInt access, DxBallInt inherit, const char *name)
{ return (DxBallHandle)OpenSemaphoreA(access, inherit, name); }
static DxBallHandle DXBALL_DDCALL create_semaphore(const DxBallSecurityAttributes *attributes,
    DxBallInt initial, DxBallInt maximum, const char *name)
{
    SECURITY_ATTRIBUTES sdk;
    memcpy(&sdk, attributes, sizeof(sdk));
    return (DxBallHandle)CreateSemaphoreA(&sdk, initial, maximum, name);
}
static DxBallInt DXBALL_DDCALL close_handle(DxBallHandle handle)
{ return CloseHandle((HANDLE)handle); }
static DxBallInt DXBALL_DDCALL version_info(DxBallVersionInfo *version)
{
    OSVERSIONINFOA sdk; BOOL result;
    memcpy(&sdk, version, sizeof(sdk)); result = GetVersionExA(&sdk);
    memcpy(version, &sdk, sizeof(sdk)); return result;
}
static DxBallUInt DXBALL_DDCALL time_ms(void) { return timeGetTime(); }
static DxBallInt DXBALL_DDCALL clock_frequency(DxBallCounter *counter)
{
    LARGE_INTEGER sdk; BOOL result;
    memcpy(&sdk, counter, sizeof(sdk)); result = QueryPerformanceFrequency(&sdk);
    memcpy(counter, &sdk, sizeof(sdk)); return result;
}
static DxBallInt DXBALL_DDCALL clock_counter(DxBallCounter *counter)
{
    LARGE_INTEGER sdk; BOOL result;
    memcpy(&sdk, counter, sizeof(sdk)); result = QueryPerformanceCounter(&sdk);
    memcpy(counter, &sdk, sizeof(sdk)); return result;
}
static DxBallInt DXBALL_DDCALL set_cursor_position(DxBallInt x, DxBallInt y)
{ return SetCursorPos(x, y); }

static DxBallHandle DXBALL_DDCALL create_file(const char *name, DxBallUInt access,
    DxBallUInt share, void *security, DxBallUInt creation, DxBallUInt flags, DxBallHandle template_file)
{
    return (DxBallHandle)CreateFileA(name, access, share, (LPSECURITY_ATTRIBUTES)security,
        creation, flags, (HANDLE)template_file);
}
static DxBallUInt DXBALL_DDCALL file_size(DxBallHandle file, DxBallUInt *high)
{
    DWORD value, result;
    if (high != NULL) value = *high;
    result = GetFileSize((HANDLE)file, high != NULL ? &value : NULL);
    if (high != NULL) *high = value;
    return result;
}
static DxBallInt DXBALL_DDCALL read_file(DxBallHandle file, void *destination,
    DxBallUInt bytes, DxBallUInt *read, void *overlapped)
{
    DWORD transferred; BOOL result;
    /* ReadFile defines this output before returning for synchronous requests. */
    result = ReadFile((HANDLE)file, destination, bytes, &transferred, (LPOVERLAPPED)overlapped);
    *read = transferred; return result;
}
static void *DXBALL_DDCALL local_alloc(DxBallUInt flags, size_t bytes)
{ return (void *)LocalAlloc(flags, bytes); }
static void *DXBALL_DDCALL local_free(void *memory) { return (void *)LocalFree((HLOCAL)memory); }
static DxBallMidiHandle DXBALL_DDCALL create_mapping(DxBallMidiHandle file, void *security,
    DxBallUInt protect, DxBallUInt high, DxBallUInt low, const char *name)
{ return (DxBallMidiHandle)CreateFileMappingA((HANDLE)file, (LPSECURITY_ATTRIBUTES)security, protect, high, low, name); }
static void *DXBALL_DDCALL map_view(DxBallMidiHandle mapping, DxBallUInt access,
    DxBallUInt high, DxBallUInt low, size_t bytes)
{ return MapViewOfFile((HANDLE)mapping, access, high, low, bytes); }
static DxBallInt DXBALL_DDCALL unmap_view(const void *memory) { return UnmapViewOfFile(memory); }
static DxBallMidiHandle DXBALL_DDCALL global_alloc(DxBallUInt flags, size_t bytes)
{ return (DxBallMidiHandle)GlobalAlloc(flags, bytes); }
static void *DXBALL_DDCALL global_lock(DxBallMidiHandle memory) { return GlobalLock((HGLOBAL)memory); }
static DxBallMidiHandle DXBALL_DDCALL global_handle(const void *memory)
{ return (DxBallMidiHandle)GlobalHandle(memory); }
static DxBallInt DXBALL_DDCALL global_unlock(DxBallMidiHandle memory) { return GlobalUnlock((HGLOBAL)memory); }
static DxBallMidiHandle DXBALL_DDCALL global_free(DxBallMidiHandle memory)
{ return (DxBallMidiHandle)GlobalFree((HGLOBAL)memory); }
static DxBallUInt DXBALL_DDCALL stream_open(DxBallMidiHandle *stream, DxBallUInt *device,
    DxBallUInt count, DxBallMidiCallback callback, size_t instance, DxBallUInt flags)
{
    HMIDISTRM sdk_stream; UINT sdk_device; MMRESULT result;
    /* Original controller always supplies CALLBACK_FUNCTION and its own callback. */
    stream_callback = callback; sdk_stream = (HMIDISTRM)*stream; sdk_device = *device;
    result = midiStreamOpen(&sdk_stream, &sdk_device, count, (DWORD)midi_callback, instance, flags);
    *stream = (DxBallMidiHandle)sdk_stream; *device = sdk_device; return result;
}
static DxBallUInt DXBALL_DDCALL stream_property(DxBallMidiHandle stream,
    DxBallMidiProperty *property, DxBallUInt flags)
{ return midiStreamProperty((HMIDISTRM)stream, (LPBYTE)property, flags); }
static DxBallUInt DXBALL_DDCALL prepare_header(DxBallMidiHandle stream, DxBallMidiHeader *header, DxBallUInt size)
{ return midiOutPrepareHeader((HMIDIOUT)stream, (LPMIDIHDR)header, size); }
static DxBallUInt DXBALL_DDCALL stream_out(DxBallMidiHandle stream, DxBallMidiHeader *header, DxBallUInt size)
{ return midiStreamOut((HMIDISTRM)stream, (LPMIDIHDR)header, size); }
static DxBallUInt DXBALL_DDCALL stream_restart(DxBallMidiHandle stream)
{ return midiStreamRestart((HMIDISTRM)stream); }
static DxBallUInt DXBALL_DDCALL stream_pause(DxBallMidiHandle stream)
{ return midiStreamPause((HMIDISTRM)stream); }
static DxBallUInt DXBALL_DDCALL out_reset(DxBallMidiHandle stream)
{ return midiOutReset((HMIDIOUT)stream); }
static DxBallUInt DXBALL_DDCALL unprepare_header(DxBallMidiHandle stream, DxBallMidiHeader *header, DxBallUInt size)
{ return midiOutUnprepareHeader((HMIDIOUT)stream, (LPMIDIHDR)header, size); }
static DxBallUInt DXBALL_DDCALL stream_close(DxBallMidiHandle stream)
{ return midiStreamClose((HMIDISTRM)stream); }

static DxBallInt DXBALL_RASTER_CALL raster_muldiv(DxBallInt number, DxBallInt numerator,
                              DxBallInt denominator)
{ return MulDiv(number, numerator, denominator); }

static void *DXBALL_HEAP_CALL heap_create(DxBallUInt flags, size_t initial, size_t maximum)
{ return (void *)HeapCreate((DWORD)flags, (DWORD)initial, (DWORD)maximum); }
static void *DXBALL_HEAP_CALL heap_allocate(void *heap, DxBallUInt flags, size_t bytes)
{ return HeapAlloc((HANDLE)heap, (DWORD)flags, (DWORD)bytes); }
static DxBallInt DXBALL_HEAP_CALL heap_release(void *heap, DxBallUInt flags, void *memory)
{ return (DxBallInt)HeapFree((HANDLE)heap, (DWORD)flags, memory); }

void dxball_bind_windows(void)
{
    FARPROC procedure;
    DxBallHeapApi heap_api;
    heap_api.create = heap_create; heap_api.allocate = heap_allocate; heap_api.release = heap_release;
    dxball_bind_heap_api(&heap_api);
    /* DLLs stay loaded for the process lifetime, including asynchronous callbacks. */
    draw_module = LoadLibraryA("ddraw.dll"); sound_module = LoadLibraryA("dsound.dll");
    procedure = draw_module != NULL ? GetProcAddress(draw_module, "DirectDrawCreate") : NULL;
    memcpy(&draw_factory, &procedure, sizeof(draw_factory));
    procedure = sound_module != NULL ? GetProcAddress(sound_module, "DirectSoundCreate") : NULL;
    memcpy(&sound_factory, &procedure, sizeof(sound_factory));
    dxball_window_api.load_icon = load_icon; dxball_window_api.load_cursor = load_cursor;
    dxball_window_api.stock_object = stock_object; dxball_window_api.register_class = register_class;
    dxball_window_api.create_window_ex = create_window; dxball_window_api.show_window = show_window;
    dxball_window_api.update_window = update_window; dxball_window_api.set_focus = set_focus;
    dxball_window_api.destroy_window = destroy_window; dxball_window_api.message_box = message_box;
    dxball_window_api.direct_draw_create = create_draw; dxball_window_api.get_cursor_pos = cursor_position;
    dxball_window_api.peek_message = peek_message; dxball_window_api.wait_message = wait_message;
    dxball_window_api.get_message = get_message; dxball_window_api.translate_message = translate_message;
    dxball_window_api.dispatch_message = dispatch_message; dxball_window_api.default_window_proc = default_proc;
    dxball_window_api.post_message = post_message; dxball_window_api.post_quit_message = post_quit;
    dxball_window_api.set_cursor = set_cursor; dxball_window_api.set_capture = set_capture;
    dxball_window_api.release_capture = release_capture; dxball_window_api.open_semaphore = open_semaphore;
    dxball_window_api.create_semaphore = create_semaphore; dxball_window_api.close_handle = close_handle;
    dxball_window_api.get_version_ex = version_info;
    dxball_clock_ops.time_ms = time_ms; dxball_clock_ops.frequency = clock_frequency;
    dxball_clock_ops.counter = clock_counter; dxball_set_cursor_position = set_cursor_position;
    dxball_raster_ops.muldiv = raster_muldiv;
    dxball_bitmap_api.create_file = create_file; dxball_bitmap_api.read_file = read_file;
    dxball_bitmap_api.local_alloc = local_alloc; dxball_bitmap_api.local_free = local_free;
    dxball_bitmap_api.close_file = close_handle;
    dxball_sound_api.create_device = create_sound; dxball_sound_api.create_file = create_file;
    dxball_sound_api.file_size = file_size; dxball_sound_api.read_file = read_file;
    dxball_sound_api.close_handle = close_handle;
    dxball_midi_local_alloc = local_alloc; dxball_midi_local_free = local_free;
    dxball_midi_create_file = create_file; dxball_midi_file_size = file_size;
    dxball_midi_create_mapping = create_mapping; dxball_midi_map_view = map_view;
    dxball_midi_unmap_view = unmap_view; dxball_midi_close_handle = close_handle;
    dxball_midi_global_alloc = global_alloc; dxball_midi_global_lock = global_lock;
    dxball_midi_global_handle = global_handle; dxball_midi_global_unlock = global_unlock;
    dxball_midi_global_free = global_free; dxball_midi_stream_open = stream_open;
    dxball_midi_stream_property = stream_property; dxball_midi_prepare_header = prepare_header;
    dxball_midi_stream_out = stream_out; dxball_midi_stream_restart = stream_restart;
    dxball_midi_stream_pause = stream_pause; dxball_midi_out_reset = out_reset;
    dxball_midi_unprepare_header = unprepare_header; dxball_midi_stream_close = stream_close;
}
