#include "runtime_arguments.h"
#include <string.h>

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
