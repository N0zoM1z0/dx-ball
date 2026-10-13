#include "runtime_arguments.h"
#include <string.h>

extern "C" {
static void dxball_crt_parse_cmdline(const unsigned char *cursor, char **argv,
                                   unsigned char *strings, int *arguments,
                                   int *characters)
{
    unsigned char character;
    int in_quote, copy_character;
    unsigned int slashes;
    *characters = 0;
    *arguments = 1;
    if (argv)
        *argv++ = (char *)strings;
    if (*cursor != '"') {
        do {
            ++*characters;
            if (strings)
                *strings++ = *cursor;
            character = *cursor++;
            if (_mbctype[character + 1] & 4) {
                ++*characters;
                if (strings)
                    *strings++ = *cursor;
                ++cursor;
            }
        } while (character != ' ' && character != 0 && character != '\t');
        if (character == 0)
            --cursor;
        else if (strings)
            strings[-1] = 0;
    } else {
        ++cursor;
        while (*cursor != '"' && *cursor != 0) {
            if (_mbctype[*cursor + 1] & 4) {
                ++*characters;
                /* Original counting pass does not consume this lead byte. */
                if (strings)
                    *strings++ = *cursor++;
            }
            ++*characters;
            if (strings)
                *strings++ = *cursor;
            ++cursor;
        }
        ++*characters;
        if (strings)
            *strings++ = 0;
        if (*cursor == '"')
            ++cursor;
    }
    in_quote = 0;
    for (;;) {
        if (*cursor == 0)
            break;
        while (*cursor == ' ' || *cursor == '\t')
            ++cursor;
        if (*cursor == 0)
            break;
        if (argv)
            *argv++ = (char *)strings;
        ++*arguments;
        for (;;) {
            copy_character = 1;
            slashes = 0;
            while (*cursor == '\\') {
                ++cursor;
                ++slashes;
            }
            if (*cursor == '"') {
                if ((slashes & 1) == 0) {
                    if (in_quote && cursor[1] == '"')
                        ++cursor;
                    else
                        copy_character = 0;
                    in_quote = !in_quote;
                }
                slashes >>= 1;
            }
            while (slashes--) {
                if (strings)
                    *strings++ = '\\';
                ++*characters;
            }
            if (*cursor == 0 || (!in_quote && (*cursor == ' ' || *cursor == '\t')))
                break;
            if (copy_character) {
                if (strings) {
                    if (_mbctype[*cursor + 1] & 4) {
                        *strings++ = *cursor++;
                        ++*characters;
                    }
                    *strings++ = *cursor++;
                    ++*characters;
                } else {
                    if (_mbctype[*cursor + 1] & 4) {
                        ++cursor;
                        ++*characters;
                    }
                    ++*characters;
                    ++cursor;
                }
            } else {
                ++cursor;
            }
        }
        if (strings)
            *strings++ = 0;
        ++*characters;
    }
    if (argv)
        *argv = 0;
    ++*arguments;
}
}

void dxball_crt_setargv(void)
{
    static char program_name[260];
    int arguments, characters;
    const unsigned char *command = (const unsigned char *)program_name;
    char **argv;
    GetModuleFileNameA(0, (char *)command, sizeof(program_name));
    _pgmptr = (char *)command;
    if (*_acmdln)
        command = (const unsigned char *)_acmdln;
    dxball_crt_parse_cmdline(command, 0, 0, &arguments, &characters);
    argv = (char **)dxball_runtime_malloc((DxBallUInt)(arguments * sizeof(*argv) + characters));
    if (argv == 0)
        dxball_crt_amsg_exit(8);
    dxball_crt_parse_cmdline(command, argv, (unsigned char *)(argv + arguments),
                             &arguments, &characters);
    __argv = argv;
    __argc = arguments - 1;
}

void dxball_crt_setenvp(void)
{
    char *entry;
    char **slot;
    int entries = 0;
    size_t length;
    for (entry = _aenvptr; *entry; entry += strlen(entry) + 1) {
        if (*entry != '=')
            ++entries;
    }
    _environ = slot = (char **)dxball_runtime_malloc((DxBallUInt)((entries + 1) * sizeof(*slot)));
    if (slot == 0)
        dxball_crt_amsg_exit(9);
    for (entry = _aenvptr; *entry; entry += length) {
        length = strlen(entry) + 1;
        if (*entry != '=') {
            *slot = (char *)dxball_runtime_malloc((DxBallUInt)length);
            if (*slot == 0)
                dxball_crt_amsg_exit(9);
            strcpy(*slot++, entry);
        }
    }
    dxball_heap_release(_aenvptr);
    *slot = 0;
}
