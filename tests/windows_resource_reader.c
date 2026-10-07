/* Read module resources through the SDK; never execute an application's entry. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int first = 1;

static void hex_bytes(const unsigned char *bytes, DWORD size)
{
    DWORD i;
    printf("\"");
    for (i = 0; i < size; ++i) printf("%02x", (unsigned int)bytes[i]);
    printf("\"");
}

static BOOL CALLBACK language_entry(HMODULE module, LPCSTR type, LPCSTR name,
                                    WORD language, LONG_PTR unused)
{
    HRSRC resource;
    HGLOBAL loaded;
    const unsigned char *bytes;
    DWORD size;
    (void)unused;
    if (!IS_INTRESOURCE(type) || !IS_INTRESOURCE(name)) return FALSE;
    resource = FindResourceExA(module, type, name, language);
    if (!resource) return FALSE;
    size = SizeofResource(module, resource);
    loaded = LoadResource(module, resource);
    bytes = (const unsigned char *)LockResource(loaded);
    if (!bytes || size > 65536) return FALSE;
    if (!first) printf(",");
    first = 0;
    printf("{\"type\":%u,\"name\":%u,\"language\":%u,\"size\":%lu,\"hex\":",
           (unsigned int)(ULONG_PTR)type, (unsigned int)(ULONG_PTR)name,
           (unsigned int)language, (unsigned long)size);
    hex_bytes(bytes, size);
    printf("}");
    return TRUE;
}

static BOOL CALLBACK name_entry(HMODULE module, LPCSTR type, LPSTR name, LONG_PTR unused)
{
    return EnumResourceLanguagesA(module, type, name, language_entry, unused);
}

static BOOL CALLBACK type_entry(HMODULE module, LPSTR type, LONG_PTR unused)
{
    return EnumResourceNamesA(module, type, name_entry, unused);
}

static int bitmap(HBITMAP handle)
{
    BITMAP object;
    BITMAPINFO info;
    HDC dc;
    unsigned char *bytes;
    DWORD size;
    int result;
    if (!GetObjectA(handle, sizeof(object), &object) || object.bmWidth != 32 ||
        object.bmHeight != 32) return 0;
    size = (DWORD)object.bmWidth * (DWORD)object.bmHeight * 4;
    bytes = (unsigned char *)malloc(size);
    if (!bytes) return 0;
    memset(&info, 0, sizeof(info));
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = object.bmWidth;
    info.bmiHeader.biHeight = -object.bmHeight;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    dc = GetDC(NULL);
    result = GetDIBits(dc, handle, 0, (UINT)object.bmHeight, bytes, &info, DIB_RGB_COLORS);
    ReleaseDC(NULL, dc);
    if (result == object.bmHeight) hex_bytes(bytes, size);
    free(bytes);
    return result == object.bmHeight;
}

int main(int argc, char **argv)
{
    HMODULE module;
    HICON requested, embedded;
    ICONINFO info;
    BOOL enumerated;
    DWORD requested_error, enumeration_error;
    if (argc != 2) return 2;
    module = LoadLibraryExA(argv[1], NULL, LOAD_LIBRARY_AS_DATAFILE);
    if (!module) return 3;
    printf("{\"resources\":[");
    SetLastError(0);
    enumerated = EnumResourceTypesA(module, type_entry, 0);
    enumeration_error = GetLastError();
    SetLastError(0);
    requested = LoadIconA(module, MAKEINTRESOURCEA(0x7f00));
    requested_error = GetLastError();
    embedded = LoadIconA(module, MAKEINTRESOURCEA(101));
    printf("],\"enumerated\":%d,\"enumeration_error\":%lu,\"requested_icon\":%d,"
           "\"requested_error\":%lu,\"embedded_icon\":%d",
           (int)enumerated, (unsigned long)enumeration_error, requested != NULL,
           (unsigned long)requested_error, embedded != NULL);
    if (embedded) {
        if (!GetIconInfo(embedded, &info)) return 4;
        printf(",\"color\":");
        if (!bitmap(info.hbmColor)) return 5;
        printf(",\"mask\":");
        if (!bitmap(info.hbmMask)) return 6;
        DeleteObject(info.hbmColor);
        DeleteObject(info.hbmMask);
    }
    printf("}\n");
    FreeLibrary(module);
    return 0;
}
