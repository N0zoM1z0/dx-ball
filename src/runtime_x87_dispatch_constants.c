#include "runtime_x87_dispatch_constants.h"

/* IEEE words preserve infinity without a runtime expression or initializer. */
const DxBallX87DispatchConstants dxball_x87_dispatch_constants = {
    {{0xffffffffU, 0x7fefffffU}}, /* DblMax */
    {{0x00000000U, 0x00100000U}}, /* DblMin */
    {{0x00000000U, 0xc0980000U}}, /* IeeeAdjO: -1536 */
    {{0x00000000U, 0x40980000U}}, /* IeeeAdjU: +1536 */
    {{0x00000000U, 0x7ff00000U}}, /* _infinity */
    {{0x00000000U, 0x00000000U}}  /* _zero */
};
