/* Persistent, read-only SDK samples. Input is supplied by the outer harness. */
#define main dxball_single_sample_main
#include "windows_state_reader.c"
#undef main

typedef struct CampaignField {
    char name[128];
    DWORD address;
    int shape;
} CampaignField;

static int read_words(HANDLE process, DWORD address, void *output, SIZE_T count)
{
    SIZE_T read;
    return ReadProcessMemory(process, (LPCVOID)address, output, count, &read)
           && read == count;
}

static int sprite_size(HANDLE process, DWORD banks, DWORD bank_address,
                       LONG slot, LONG *width, LONG *height)
{
    DWORD bank, sprite;
    LONG dimensions[2];
    if (slot < 0 || slot >= 255 || !read_words(process, bank_address, &bank, 4)
        || bank > 2 || !read_words(process, banks + bank * 1048 + (DWORD)slot * 4,
                                  &sprite, 4)
        || !sprite || !read_words(process, sprite + 8, dimensions, 8)) return 0;
    *width = dimensions[0]; *height = dimensions[1];
    return *width > 0 && *width <= 640 && *height > 0 && *height <= 480;
}

static int print_nodes(HANDLE process, DWORD address, int bonus,
                       DWORD banks, DWORD bank_address)
{
    DWORD pointer, next, visited[128];
    LONG data[13], width, height;
    int first = 1, count = 0, i;
    if (!read_words(process, address + 4, &pointer, 4)) return 0;
    printf("[");
    while (pointer && count < 128) {
        for (i = 0; i < count; ++i) if (visited[i] == pointer) return 0;
        visited[count++] = pointer;
        if (!read_words(process, pointer, data, bonus ? 28 : 52)
            || !read_words(process, pointer + (bonus ? 28 : 52), &next, 4)
            || !sprite_size(process, banks, bank_address, data[bonus ? 1 : 6],
                            &width, &height)) return 0;
        printf("%s{\"x\":%ld,\"y\":%ld,\"dx\":%ld,\"dy\":%ld,"
               "\"width\":%ld,\"height\":%ld", first ? "" : ",",
               (long)data[bonus ? 2 : 0], (long)data[bonus ? 3 : 1],
               (long)data[4], (long)data[5], (long)width, (long)height);
        if (bonus) printf(",\"kind\":%ld,\"gravity_ticks\":%ld",
                          (long)data[0], (long)data[6]);
        else printf(",\"attached\":%ld", (long)data[10]);
        printf("}"); first = 0; pointer = next;
    }
    if (pointer) return 0;
    printf("]"); return 1;
}

int main(int argc, char **argv)
{
    CampaignField fields[64];
    HWND window;
    HANDLE process;
    HMODULE local = NULL;
    DWORD pid, base = 0, banks = 0, bank_address = 0, value;
    char *separator, *shape, *end;
    const char *basename;
    int first = 2, i, count, ok, code = 0;
    if (sizeof(void *) != 4 || argc < 3) return 2;
    window = FindWindowA("DX-Ball", "DX-Ball");
    if (!window) return 3;
    GetWindowThreadProcessId(window, &pid);
    process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | SYNCHRONIZE,
                          FALSE, pid);
    if (!process) return 4;
    if (strcmp(argv[1], "dll") == 0) {
        if (argc < 4) { code = 2; goto done; }
        local = LoadLibraryExA(argv[2], NULL, DONT_RESOLVE_DLL_REFERENCES);
        if (!local) { code = 5; goto done; }
        basename = strrchr(argv[2], '\\');
        base = module_base(pid, basename ? basename + 1 : argv[2]);
        if (!base) { code = 6; goto done; }
        first = 3;
    } else if (strcmp(argv[1], "addresses") != 0) { code = 2; goto done; }
    count = argc - first;
    if (count > 64) { code = 2; goto done; }
    for (i = 0; i < count; ++i) {
        const char *argument = argv[i + first];
        if (strlen(argument) >= sizeof(fields[i].name)) { code = 2; goto done; }
        strcpy(fields[i].name, argument); fields[i].address = 0; fields[i].shape = 0;
        separator = strchr(fields[i].name, '=');
        if (!local) {
            if (!separator) { code = 2; goto done; }
            *separator++ = '\0'; fields[i].address = strtoul(separator, &end, 0);
            if (*end) { code = 2; goto done; }
        }
        shape = strchr(fields[i].name, ':');
        if (shape) {
            if (strcmp(shape, ":ball_list") == 0) fields[i].shape = 1;
            else if (strcmp(shape, ":bonus_list") == 0) fields[i].shape = 2;
            else if (strcmp(shape, ":board") == 0) fields[i].shape = 3;
            else { code = 2; goto done; }
            *shape = '\0';
        }
        if (local) {
            FARPROC symbol = GetProcAddress(local, fields[i].name);
            fields[i].address = symbol ? base + (DWORD)symbol - (DWORD)local :
                storage_field(process, local, base, fields[i].name);
        }
        if (!fields[i].address) { code = 7; goto done; }
        if (strcmp(fields[i].name, "dxball_sprite_banks") == 0 ||
            strcmp(fields[i].name, "sprite_banks") == 0) banks = fields[i].address;
        if (strcmp(fields[i].name, "dxball_sprite_bank") == 0 ||
            strcmp(fields[i].name, "sprite_bank") == 0) bank_address = fields[i].address;
    }
    if (!banks || !bank_address) { code = 2; goto done; }
    /* One pipe write per sample instead of one write per hex byte. */
    setvbuf(stdout, NULL, _IOFBF, 4096);
    while (IsWindow(window) && WaitForSingleObject(process, 0) == WAIT_TIMEOUT) {
        POINT origin;
        origin.x = origin.y = 0;
        if (!ClientToScreen(window, &origin)) { code = 8; break; }
        printf("{\"pid\":%lu,\"origin\":[%ld,%ld],\"values\":{",
               (unsigned long)pid, (long)origin.x, (long)origin.y);
        ok = 1;
        for (i = 0; i < count; ++i) {
            if (i) printf(",");
            printf("\"%s\":", fields[i].name);
            if (fields[i].shape == 1 || fields[i].shape == 2) {
                if (!print_nodes(process, fields[i].address, fields[i].shape == 2,
                                 banks, bank_address)) { ok = 0; break; }
            } else if (fields[i].shape == 3) {
                if (!print_bytes(process, fields[i].address, 400)) { ok = 0; break; }
            } else {
                if (!read_words(process, fields[i].address, &value, 4)) { ok = 0; break; }
                printf("%ld", (long)(LONG)value);
            }
        }
        if (ok) printf("}}\n");
        else { printf("BROKEN_SAMPLE\n"); }
        fflush(stdout);
        Sleep(10);
    }
done:
    if (local) FreeLibrary(local);
    CloseHandle(process);
    if (code) fprintf(stderr, "Campaign reader failed: %d / Win32 %lu\n", code,
                      (unsigned long)GetLastError());
    return code;
}
