#include "termination.h"
#include "termination_process_api.h"
#include <stddef.h>

DxBallTerminationOps dxball_termination_ops;
unsigned int dxball_termination_done;
unsigned char dxball_exit_flag;
DxBallCrtCallback *dxball_onexit_begin;
DxBallCrtCallback *dxball_onexit_end;

void dxball_crt_run_initializers(DxBallCrtCallback *first,
                                 DxBallCrtCallback *last)
{
    while (first < last) {
        if (*first)
            (*first)();
        ++first;
    }
}

void dxball_crt_do_exit(unsigned int status, int quick, int return_to_caller)
{
    size_t cursor;
    dxball_termination_done = 1;
    dxball_exit_flag = (unsigned char)return_to_caller;
    if (!quick) {
        if (dxball_onexit_begin) {
            /* Decrement before comparison, without forming a before-array
               pointer on the original empty-table path. */
            cursor = (size_t)(void *)dxball_onexit_end - sizeof(DxBallCrtCallback);
            while (cursor >= (size_t)(void *)dxball_onexit_begin) {
                DxBallCrtCallback *slot = (DxBallCrtCallback *)(void *)cursor;
                if (*slot)
                    (*slot)();
                cursor -= sizeof(DxBallCrtCallback);
            }
        }
        dxball_crt_run_initializers(dxball_preterminators,
                                   dxball_preterminators + 2);
    }
    dxball_crt_run_initializers(dxball_terminators, dxball_terminators + 1);
    if (!return_to_caller)
        ExitProcess(status);
}

void dxball_crt_exit(unsigned int status)
{
    dxball_crt_do_exit(status, 0, 0);
}

void dxball_crt_quick_exit(unsigned int status)
{
    dxball_crt_do_exit(status, 1, 0);
}
