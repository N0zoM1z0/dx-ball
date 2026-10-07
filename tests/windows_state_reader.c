/* Read-only runtime observation. No target writes, hooks or thread suspension. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static DWORD module_base(DWORD pid, const char *name)
{
    HANDLE snapshot;
    MODULEENTRY32 record;
    DWORD result = 0;
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;
    memset(&record, 0, sizeof(record)); record.dwSize = sizeof(record);
    if (Module32First(snapshot, &record)) {
        do {
            if (lstrcmpiA(record.szModule, name) == 0) {
                result = (DWORD)record.modBaseAddr; break;
            }
        } while (Module32Next(snapshot, &record));
    }
    CloseHandle(snapshot); return result;
}

static int print_ball(HANDLE process, DWORD address)
{
    static const char *const names[13] = {"x", "y", "previous_x", "previous_y",
        "dx", "dy", "sprite", "angle", "speed", "bounce_count", "attached",
        "attach_offset", "wall_bounces"};
    DWORD first, fields[13];
    SIZE_T read;
    int index;
    /* Retained x86/source layout: list.first at +4; 13 signed fields before links. */
    if (!ReadProcessMemory(process, (LPCVOID)(address + 4), &first, sizeof(first), &read)
            || read != sizeof(first)) return 0;
    if (first == 0) { printf("null"); return 1; }
    if (!ReadProcessMemory(process, (LPCVOID)first, fields, sizeof(fields), &read)
            || read != sizeof(fields)) return 0;
    printf("{");
    for (index = 0; index < 13; ++index)
        printf("%s\"%s\":%ld", index == 0 ? "" : ",", names[index], (long)(LONG)fields[index]);
    printf("}"); return 1;
}

int main(int argc, char **argv)
{
    HWND window;
    HANDLE process = NULL;
    HMODULE local = NULL;
    DWORD pid = 0, base = 0, address, value;
    SIZE_T read;
    const char *name, *separator, *basename;
    char symbol[128], *end, *shape;
    int first, index, ball, code = 1;
    if (sizeof(void *) != 4 || argc < 3) return 2;
    window = FindWindowA("DX-Ball", "DX-Ball");
    if (window == NULL) { fprintf(stderr, "No DX-Ball window\n"); return 3; }
    GetWindowThreadProcessId(window, &pid);
    process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (process == NULL) goto failure;
    first = 2;
    if (strcmp(argv[1], "dll") == 0) {
        if (argc < 4) goto failure;
        local = LoadLibraryExA(argv[2], NULL, DONT_RESOLVE_DLL_REFERENCES);
        if (local == NULL) goto failure;
        basename = strrchr(argv[2], '\\');
        name = basename == NULL ? argv[2] : basename + 1;
        base = module_base(pid, name);
        if (base == 0) goto failure;
        first = 3;
    } else if (strcmp(argv[1], "addresses") != 0) goto failure;
    printf("{\"pid\":%lu,\"values\":{", (unsigned long)pid);
    for (index = first; index < argc; ++index) {
        address = 0;
        if (local != NULL) {
            if (strlen(argv[index]) >= sizeof(symbol)) goto failure;
            strcpy(symbol, argv[index]);
        } else {
            separator = strchr(argv[index], '=');
            if (separator == NULL || separator - argv[index] >= (int)sizeof(symbol)) goto failure;
            memcpy(symbol, argv[index], (size_t)(separator - argv[index]));
            symbol[separator - argv[index]] = '\0';
            address = strtoul(separator + 1, &end, 0);
            if (*end != '\0') goto failure;
        }
        name = symbol; shape = strchr(symbol, ':'); ball = shape != NULL;
        if (ball) {
            if (strcmp(shape, ":ball") != 0) goto failure;
            *shape = '\0';
        }
        if (strspn(name, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != strlen(name)) goto failure;
        if (local != NULL) {
            FARPROC procedure = GetProcAddress(local, name);
            if (procedure == NULL) goto failure;
            address = base + (DWORD)procedure - (DWORD)local;
        }
        if (address == 0) goto failure;
        printf("%s\"%s\":", index == first ? "" : ",", name);
        if (ball) {
            if (!print_ball(process, address)) goto failure;
        } else {
            if (!ReadProcessMemory(process, (LPCVOID)address, &value, sizeof(value), &read)
                || read != sizeof(value)) goto failure;
            printf("%ld", (long)(LONG)value);
        }
    }
    printf("}}\n"); code = 0;
failure:
    if (code != 0) fprintf(stderr, "State reader failed (Win32 error %lu)\n", (unsigned long)GetLastError());
    if (local != NULL) FreeLibrary(local);
    if (process != NULL) CloseHandle(process);
    return code;
}
