#include "runtime_cpp_unwind.h"
#include <excpt.h>

/* FUNCTION: DXBALL 0x0041B690 */
void dxball_cpp_frame_unwind_to_state(DxBallCppRegistration *registration,
    void *, const DxBallCppFunctionPrefix *function, int target_state)
{
    int &registration_state = registration->state;
    int state = registration_state;
    while (state != target_state) {
        if (state <= -1 || state >= function->max_state)
            dxball_cpp_inconsistency();
        __try {
            void (*action)(void) =
                ((const DxBallCppUnwindEntry *)function->unwind_map)[state].action;
            if (action)
                _CallSettingFrame((void *)action, registration, 0x103);
        } __except (dxball_cpp_frame_unwind_filter(
                (DxBallCppExceptionPointers *)_exception_info())) {
        }
        state = ((const DxBallCppUnwindEntry *)function->unwind_map)[state].to_state;
    }
    if (state != target_state)
        dxball_cpp_inconsistency();
    registration_state = state;
}
