#include "runtime_stdio_initialization.h"

char dxball_crt_standard_input_buffer[4096];

DxBallCrtStream dxball_crt_standard_streams[20] = {
    { dxball_crt_standard_input_buffer, 0, dxball_crt_standard_input_buffer,
      0x101, 0, 0, 4096, NULL },
    { NULL, 0, NULL, 2, 1, 0, 0, NULL },
    { NULL, 0, NULL, 2, 2, 0, 0, NULL }
};

int dxball_crt_buffer_requests = 0;
int dxball_crt_stream_limit;
DxBallCrtStream **dxball_crt_streams;
