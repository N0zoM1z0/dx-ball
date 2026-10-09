#include "termination.h"

DxBallTerminationOps dxball_termination_ops;
unsigned int dxball_termination_done;
unsigned char dxball_exit_flag;
DxBallCrtCallback *dxball_onexit_begin;
DxBallCrtCallback *dxball_onexit_end;
DxBallCrtCallback dxball_preterminators[2];
DxBallCrtCallback dxball_terminators[1];

/* 0x4179D0: bounds are local arguments; callback slots are read as visited. */
void dxball_crt_run_initializers(DxBallCrtCallback *first,
                                 DxBallCrtCallback *last)
{
    while (first < last) {
        if (*first)
            (*first)();
        ++first;
    }
}

/* 0x417950: the reverse walk captures the end but reloads the global begin. */
void dxball_crt_do_exit(unsigned int status, int quick, int return_to_caller)
{
    DxBallCrtCallback *cursor;
    dxball_termination_done = 1;
    dxball_exit_flag = (unsigned char)return_to_caller;
    if (!quick) {
        if (dxball_onexit_begin) {
            cursor = dxball_onexit_end;
            while (cursor > dxball_onexit_begin) {
                --cursor;
                if (*cursor)
                    (*cursor)();
            }
        }
        dxball_crt_run_initializers(dxball_preterminators,
                                   dxball_preterminators + 2);
    }
    dxball_crt_run_initializers(dxball_terminators, dxball_terminators + 1);
    if (!return_to_caller)
        dxball_termination_ops.exit_process(status);
}

/* 0x417910: normal exit, including on-exit and pretermination callbacks. */
void dxball_crt_exit(unsigned int status)
{
    dxball_crt_do_exit(status, 0, 0);
}

/* 0x417930: C _exit still executes the termination table in this CRT. */
void dxball_crt_quick_exit(unsigned int status)
{
    dxball_crt_do_exit(status, 1, 0);
}
