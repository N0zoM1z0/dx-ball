/* Source-owned x86 copy driver. Never attaches to or modifies the game. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef void (__cdecl *CopyBoard)(int);
typedef void (__cdecl *InitializeBoard)(void);

int main(int argc, char **argv)
{
    HMODULE module;
    FILE *input, *output;
    unsigned char *storage, *aux;
    unsigned int *offsets;
    int *index;
    FARPROC entry;
    CopyBoard load, store;
    InitializeBoard initialize;
    unsigned int count, row, operation, board;
    unsigned char image[20432], auxiliary[400];
    int selected;
    if (argc != 4) return 2;
    module = LoadLibraryA(argv[1]);
    if (!module) return 3;
    storage = (unsigned char *)(ULONG_PTR)GetProcAddress(module, "dxball_board_storage");
    offsets = (unsigned int *)(ULONG_PTR)GetProcAddress(module, "dxball_board_storage_offsets");
    aux = (unsigned char *)(ULONG_PTR)GetProcAddress(module, "dxball_board_aux");
    index = (int *)(ULONG_PTR)GetProcAddress(module, "dxball_board_index");
    entry = GetProcAddress(module, "dxball_load_editor_board");
    if (!entry) return 4;
    memcpy(&load, &entry, sizeof(load));
    entry = GetProcAddress(module, "dxball_store_editor_board");
    if (!entry) return 4;
    memcpy(&store, &entry, sizeof(store));
    entry = GetProcAddress(module, "dxball_initialize_board");
    if (!entry) return 4;
    memcpy(&initialize, &entry, sizeof(initialize));
    if (!storage || !offsets || !aux || !index || sizeof(void *) != 4 ||
        offsets[0] != 0 || offsets[1] != 20000 || offsets[2] != 20008 ||
        offsets[3] != 20024 || offsets[4] != 20032 || offsets[5] != sizeof(image)) return 5;
    input = fopen(argv[2], "rb");
    output = fopen(argv[3], "wb");
    if (!input || !output) return 6;
    if (fread(&count, 4, 1, input) != 1 || fwrite(offsets, 4, 6, output) != 6) return 7;
    for (row = 0; row < count; ++row) {
        if (fread(&operation, 4, 1, input) != 1 || fread(&board, 4, 1, input) != 1 ||
            fread(&selected, 4, 1, input) != 1 || fread(image, 1, sizeof(image), input) != sizeof(image) ||
            fread(auxiliary, 1, sizeof(auxiliary), input) != sizeof(auxiliary) ||
            operation > 2 || board > 50 || selected < 0 || selected > 50) return 8;
        memcpy(storage, image, sizeof(image));
        memcpy(aux, auxiliary, sizeof(auxiliary));
        *index = selected;
        if (operation == 0) load((int)board);
        else if (operation == 1) store((int)board);
        else initialize();
        if (fwrite(storage, 1, sizeof(image), output) != sizeof(image) ||
            fwrite(aux, 1, sizeof(auxiliary), output) != sizeof(auxiliary) ||
            fwrite(index, 4, 1, output) != 1) return 9;
    }
    if (fgetc(input) != EOF || fclose(input) || fclose(output)) return 10;
    FreeLibrary(module);
    return 0;
}
