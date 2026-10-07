#include "boards.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* Host utility; this entry point is not a reconstructed game function. */
int main(int argc, char **argv)
{
    char *end;
    long board;
    long size;
    FILE *input;
    int x, y;
    if (argc != 3) {
        fprintf(stderr, "usage: %s DEFAULT.BDS BOARD_NUMBER(1..50)\n", argv[0]);
        return 2;
    }
    errno = 0;
    board = strtol(argv[2], &end, 10);
    if (errno != 0 || end == argv[2] || *end != '\0' || board < 1 || board > 50) {
        fprintf(stderr, "board number must be 1..50\n");
        return 2;
    }
    input = fopen(argv[1], "rb");
    if (input == NULL) {
        perror(argv[1]);
        return 1;
    }
    if (fseek(input, 0, SEEK_END) != 0) {
        fclose(input);
        return 1;
    }
    size = ftell(input);
    fclose(input);
    if (size != DXBALL_BOARD_BANK_SIZE) {
        fprintf(stderr, "board bank must contain exactly 20000 bytes\n");
        return 1;
    }
    dxball_read_board_bank(argv[1]);
    if (dxball_board_file == NULL) {
        fprintf(stderr, "board bank could not be reopened\n");
        return 1;
    }
    dxball_board_index = (DxBallInt)board - 1;
    dxball_initialize_board();
    printf("{\"board\":%ld,\"width\":20,\"height\":20,\"tiles\":[", board);
    for (y = 0; y < DXBALL_BOARD_HEIGHT; ++y) {
        printf("%s[", y == 0 ? "" : ",");
        for (x = 0; x < DXBALL_BOARD_WIDTH; ++x) {
            printf("%s%u", x == 0 ? "" : ",",
                   (unsigned)dxball_board_tiles[x + y * DXBALL_BOARD_WIDTH]);
        }
        printf("]");
    }
    printf("]}\n");
    return 0;
}
