#include "runtime_cpp_tables.h"

#pragma pack(push, 1)
#if defined(__GNUC__)
typedef struct __attribute__((__may_alias__)) DxBallCppStateBounds {
#else
typedef struct DxBallCppStateBounds {
#endif
    int try_high, catch_high;
} DxBallCppStateBounds;
#pragma pack(pop)

int dxball_cpp_frame_unwind_filter(DxBallCppExceptionPointers *pointers)
{
    if (pointers->record->code == 0xe06d7363U)
        dxball_cpp_terminate();
    return 0;
}

void *dxball_cpp_adjust_pointer(void *object, const DxBallCppPmd &displacement)
{
    char *base = (char *)object;
    char *adjusted = base + displacement.member_displacement;
    int vbptr = displacement.vbptr_displacement;
    if (vbptr >= 0) {
        const int *table = *(const int *const *)(const void *)(base + vbptr);
        adjusted += *(const int *)(const void *)((const char *)table + displacement.virtual_displacement);
        adjusted += vbptr;
    }
    return adjusted;
}

const DxBallCppTryEntry *dxball_cpp_select_try_range(const DxBallCppFunctionPrefix *function,
    int nesting, int state, unsigned int *low, unsigned int *high)
{
    const DxBallCppTryEntry *tries = function->try_map;
    unsigned int index = function->try_count;
    unsigned int end = index, previous = index;
    if (nesting >= 0) {
        const char *cursor = (const char *)(const void *)tries + index * sizeof(*tries)
            + offsetof(DxBallCppTryEntry, try_high);
        do {
            if (index == ~0U)
                dxball_cpp_inconsistency();
            cursor -= sizeof(*tries);
            --index;
            /* The original reads the two state words before testing its
               wrapped sentinel. Backing includes that real prefix byte span;
               the byte cursor does not form a before-array entry pointer. */
            const DxBallCppStateBounds *bounds = (const DxBallCppStateBounds *)(const void *)
                cursor;
            if ((bounds->try_high < state && state <= bounds->catch_high) || index == ~0U) {
                --nesting;
                end = previous;
                previous = index;
            }
        } while (nesting >= 0);
    }
    ++index;
    *low = index;
    *high = end;
    if (function->try_count < end || end < index)
        dxball_cpp_inconsistency();
    return tries + index;
}

void dxball_cpp_find_foreign_handler(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, DxBallCppContext *context, void *dispatcher,
    const DxBallCppFunctionPrefix *function, int state, int nesting,
    DxBallCppRegistration *marker)
{
    unsigned int low, high;
    const DxBallCppTryEntry *entry;
    if (__pSETranslator && dxball_cpp_call_se_translator(exception, registration,
            context, dispatcher, function, nesting, marker))
        return;
    entry = dxball_cpp_select_try_range(function, nesting, state, &low, &high);
    while (low < high) {
        if (entry->try_low <= state && state <= entry->try_high) {
            const DxBallCppHandler *end = entry->handlers + entry->catch_count;
            if (!end[-1].type || end[-1].type->name[0] == 0)
                dxball_cpp_catch_it(exception, registration, context, dispatcher,
                    function, end - 1, 0, entry, nesting, marker);
        }
        ++entry;
        ++low;
    }
}
