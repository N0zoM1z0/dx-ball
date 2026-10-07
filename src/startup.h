#ifndef DXBALL_STARTUP_H
#define DXBALL_STARTUP_H
#include "boards.h"

typedef struct DxBallScoreRecord { char name[40]; DxBallUInt score; } DxBallScoreRecord;
typedef struct DxBallStartupFileOps {
    FILE *(*open)(const char *, const char *);
    size_t (*read)(void *, size_t, size_t, FILE *);
    size_t (*write)(const void *, size_t, size_t, FILE *);
    DxBallInt (*close)(FILE *);
    DxBallInt (*access)(const char *, DxBallInt);
} DxBallStartupFileOps;
typedef struct DxBallRandomOps {
    void (*seed)(DxBallUInt);
    DxBallInt (*next)(void);
} DxBallRandomOps;
extern DxBallScoreRecord dxball_scores[15];
extern char dxball_board_filename[12];
extern DxBallStartupFileOps dxball_startup_file_ops;
extern DxBallRandomOps dxball_random_ops;
extern void (*dxball_startup_load_boards)(const char *path);
void dxball_initialize_device_state(void);
void dxball_initialize_scores(void);
void dxball_read_scores(void);
void dxball_seed_random(void);
DxBallInt dxball_random_range(DxBallInt limit);
void dxball_release_sprite_banks(void);
#endif
