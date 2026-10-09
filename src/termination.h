#ifndef DXBALL_TERMINATION_H
#define DXBALL_TERMINATION_H

typedef void (*DxBallCrtCallback)(void);

/* Host-width callback storage. Valid table bounds belong to the same array.
   Supply the platform boundary before using a nonreturning exit mode. */
typedef struct DxBallTerminationOps {
    void (*exit_process)(unsigned int status);
} DxBallTerminationOps;

extern DxBallTerminationOps dxball_termination_ops;
extern unsigned int dxball_termination_done;
extern unsigned char dxball_exit_flag;
extern DxBallCrtCallback *dxball_onexit_begin;
extern DxBallCrtCallback *dxball_onexit_end;
extern DxBallCrtCallback dxball_preterminators[2];
extern DxBallCrtCallback dxball_terminators[1];

void dxball_crt_run_initializers(DxBallCrtCallback *first,
                                 DxBallCrtCallback *last);
void dxball_crt_do_exit(unsigned int status, int quick, int return_to_caller);
void dxball_crt_exit(unsigned int status);
void dxball_crt_quick_exit(unsigned int status);

#endif
