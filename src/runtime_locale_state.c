#include "runtime_locale_state.h"

/* Complete nlsdata1 ownership; native size_t grows with the host ABI. */
int __mb_cur_max = 1;
char __decimal_point[] = ".";
size_t __decimal_point_length = 1;
