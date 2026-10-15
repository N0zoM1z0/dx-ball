#include "runtime_arguments.h"
#include <string.h>

extern "C" {
static void dxball_crt_parse_cmdline(char *cursor, char **argv,
                                   char *strings, int *arguments,
                                   int *characters);
}

void dxball_crt_setargv(void)
{
    static char program_name[260];
    int arguments, characters;
    char *command;
    char *block;
    GetModuleFileNameA(0, program_name, sizeof(program_name));
    _pgmptr = program_name;
    command = (*_acmdln == 0) ? _pgmptr : _acmdln;
    dxball_crt_parse_cmdline(command, 0, 0, &arguments, &characters);
    block = (char *)dxball_runtime_malloc((DxBallUInt)(arguments * sizeof(char *) + characters));
    if (block == 0)
        dxball_crt_amsg_exit(8);
    dxball_crt_parse_cmdline(command, (char **)block, block + arguments * sizeof(char *),
                             &arguments, &characters);
    __argc = arguments - 1;
    __argv = (char **)block;
}

extern "C" {
static void dxball_crt_parse_cmdline(char *command, char **argv,
                                   char *strings, int *arguments,
                                   int *characters)
{
    char *cursor;
    unsigned char character;
    int in_quote, copy_character;
    unsigned int slashes;
    *characters = 0;
    *arguments = 1;
    cursor = command;
    if (argv)
        *argv++ = (char *)strings;
    if (*cursor == '"') {
        while (*++cursor != '"' && *cursor != 0) {
            if (_mbctype[(unsigned char)*cursor + 1] & 4) {
                ++*characters;
                /* Original counting pass does not consume this lead byte. */
                if (strings)
                    *strings++ = *cursor++;
            }
            ++*characters;
            if (strings)
                *strings++ = *cursor;
        }
        ++*characters;
        if (strings)
            *strings++ = 0;
        if (*cursor == '"')
            ++cursor;
    } else {
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
    }
    in_quote = 0;
    for (;;) {
        if (*cursor) {
            while (*cursor == ' ' || *cursor == '\t')
                ++cursor;
        }
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
                    if (in_quote) {
                        if (cursor[1] == '"')
                            ++cursor;
                        else
                            copy_character = 0;
                    } else {
                        copy_character = 0;
                    }
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
                    if (_mbctype[(unsigned char)*cursor + 1] & 4) {
                        *strings++ = *cursor++;
                        ++*characters;
                    }
                    *strings++ = *cursor;
                } else {
                    if (_mbctype[(unsigned char)*cursor + 1] & 4) {
                        ++cursor;
                        ++*characters;
                    }
                }
                ++*characters;
            }
            ++cursor;
        }
        if (strings)
            *strings++ = 0;
        ++*characters;
    }
    if (argv)
        *argv++ = 0;
    ++*arguments;
}
}
