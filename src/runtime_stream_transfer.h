#ifndef DXBALL_RUNTIME_STREAM_TRANSFER_H
#define DXBALL_RUNTIME_STREAM_TRANSFER_H

#include "runtime_lowio_read.h"
#include "runtime_stream.h"

#ifdef __cplusplus
extern "C" {
#endif
extern int dxball_crt_stream_limit;
extern DxBallCrtStream dxball_crt_standard_streams[];
extern DxBallLowioRecord dxball_crt_invalid_io;

int dxball_crt_fclose(DxBallCrtStream *stream);
unsigned int dxball_crt_fread(void *buffer, unsigned int element_size,
                            unsigned int elements, DxBallCrtStream *stream);
DxBallCrtStream *dxball_crt_get_stream(void);
int dxball_crt_fill_input(DxBallCrtStream *stream);
int dxball_crt_flush_output(int value, DxBallCrtStream *stream);
int dxball_crt_isatty(int descriptor);
#ifdef __cplusplus
}
#endif
#endif
