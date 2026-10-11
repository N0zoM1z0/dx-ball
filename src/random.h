#ifndef DXBALL_RANDOM_H
#define DXBALL_RANDOM_H

#include "state_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Recovered single-threaded VC4 state, initially one. */
extern DxBallUInt dxball_random_state;
void dxball_crt_srand(DxBallUInt seed);
DxBallInt dxball_crt_rand(void);

#ifdef __cplusplus
}
#endif

#endif
