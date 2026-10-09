/* Check the maintained i686 records against actual Win32/WinMM SDK headers.
   This is adapter evidence, not an original-entry or driver-behavior claim. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <stddef.h>
#include <stdio.h>
#include "../src/sound.h"
#include "../src/midi.h"
#include "../src/core.h"

#define CHECK(expression, name) typedef char name[(expression) ? 1 : -1]
#define FIELD(ours, own_field, sdk, sdk_field, name) \
    CHECK(offsetof(ours, own_field) == offsetof(sdk, sdk_field), name)

CHECK(sizeof(void *) == 4, i686_pointers_required);
CHECK(sizeof(DxBallHandle) == sizeof(HANDLE), handle_size);
CHECK(sizeof(DxBallWindowResult) == sizeof(LRESULT), result_size);
CHECK(sizeof(DxBallPoint) == sizeof(POINT), point_size);
CHECK(sizeof(DxBallMessage) == sizeof(MSG), message_size);
FIELD(DxBallMessage, window, MSG, hwnd, message_window);
FIELD(DxBallMessage, message, MSG, message, message_id);
FIELD(DxBallMessage, wparam, MSG, wParam, message_wparam);
FIELD(DxBallMessage, lparam, MSG, lParam, message_lparam);
FIELD(DxBallMessage, time, MSG, time, message_time);
FIELD(DxBallMessage, point, MSG, pt, message_point);
CHECK(sizeof(DxBallWindowClass) == sizeof(WNDCLASSA), window_class_size);
FIELD(DxBallWindowClass, procedure, WNDCLASSA, lpfnWndProc, window_class_proc);
FIELD(DxBallWindowClass, instance, WNDCLASSA, hInstance, window_class_instance);
FIELD(DxBallWindowClass, menu, WNDCLASSA, lpszMenuName, window_class_menu);
FIELD(DxBallWindowClass, name, WNDCLASSA, lpszClassName, window_class_name);
CHECK(sizeof(DxBallSecurityAttributes) == sizeof(SECURITY_ATTRIBUTES), security_size);
FIELD(DxBallSecurityAttributes, descriptor, SECURITY_ATTRIBUTES, lpSecurityDescriptor, security_descriptor);
CHECK(sizeof(DxBallVersionInfo) == sizeof(OSVERSIONINFOA), version_size);
CHECK(sizeof(DxBallCounter) == sizeof(LARGE_INTEGER), counter_size);
CHECK(sizeof(DxBallMidiHeader) == sizeof(MIDIHDR), midi_header_size);
FIELD(DxBallMidiHeader, data, MIDIHDR, lpData, midi_data);
FIELD(DxBallMidiHeader, buffer_length, MIDIHDR, dwBufferLength, midi_length);
FIELD(DxBallMidiHeader, bytes_recorded, MIDIHDR, dwBytesRecorded, midi_recorded);
FIELD(DxBallMidiHeader, user, MIDIHDR, dwUser, midi_user);
FIELD(DxBallMidiHeader, flags, MIDIHDR, dwFlags, midi_flags);
FIELD(DxBallMidiHeader, next, MIDIHDR, lpNext, midi_next);
FIELD(DxBallMidiHeader, reserved, MIDIHDR, reserved, midi_reserved);
FIELD(DxBallMidiHeader, offset, MIDIHDR, dwOffset, midi_offset);
FIELD(DxBallMidiHeader, reserved_array, MIDIHDR, dwReserved, midi_array);
CHECK(sizeof(DxBallMidiProperty) == sizeof(MIDIPROPTIMEDIV), midi_property_size);
FIELD(DxBallMidiProperty, value, MIDIPROPTIMEDIV, dwTimeDiv, midi_property_value);
CHECK(sizeof(DxBallSound) == 36, sound_record_size);
CHECK(offsetof(DxBallSound, filename) == 4, sound_record_filename);
CHECK(offsetof(DxBallSound, frequency) == 24, sound_record_frequency);
CHECK(offsetof(DxBallSound, pan) == 28, sound_record_pan);
CHECK(offsetof(DxBallSound, volume) == 32, sound_record_volume);
CHECK(sizeof(DxBallSoundBufferDesc) == 20, sound_desc_size);
CHECK(offsetof(DxBallSoundBufferDesc, format) == 16, sound_desc_format);
CHECK(sizeof(DxBallProjectileNode) == 24, projectile_node_size);
CHECK(offsetof(DxBallProjectileNode, next) == 16, projectile_next);
CHECK(offsetof(DxBallProjectileNode, previous) == 20, projectile_previous);
CHECK(sizeof(DxBallProjectileList) == 16, projectile_list_size);
CHECK(offsetof(DxBallProjectileList, current) == 0, projectile_current);
CHECK(offsetof(DxBallProjectileList, first) == 4, projectile_first);
CHECK(offsetof(DxBallProjectileList, last) == 8, projectile_last);
CHECK(sizeof(DxBallFireEffectNode) == 20, fire_node_size);
CHECK(offsetof(DxBallFireEffectNode, next) == 12, fire_next);
CHECK(offsetof(DxBallFireEffectNode, previous) == 16, fire_previous);
CHECK(sizeof(DxBallFireEffectList) == 16, fire_list_size);

int main(void)
{
    printf("{\"pointer\":%u,\"message\":%u,\"window_class\":%u,"
           "\"security\":%u,\"version\":%u,\"counter\":%u,"
           "\"midi_header\":%u,\"midi_property\":%u,"
           "\"sound_record\":%u,\"sound_desc\":%u,\"projectile_node\":%u,"
           "\"projectile_list\":%u,\"fire_node\":%u,\"fire_list\":%u}\n",
           (unsigned)sizeof(void *), (unsigned)sizeof(MSG),
           (unsigned)sizeof(WNDCLASSA), (unsigned)sizeof(SECURITY_ATTRIBUTES),
           (unsigned)sizeof(OSVERSIONINFOA), (unsigned)sizeof(LARGE_INTEGER),
           (unsigned)sizeof(MIDIHDR), (unsigned)sizeof(MIDIPROPTIMEDIV),
           (unsigned)sizeof(DxBallSound), (unsigned)sizeof(DxBallSoundBufferDesc),
           (unsigned)sizeof(DxBallProjectileNode), (unsigned)sizeof(DxBallProjectileList),
           (unsigned)sizeof(DxBallFireEffectNode), (unsigned)sizeof(DxBallFireEffectList));
    return 0;
}
