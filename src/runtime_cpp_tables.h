#ifndef DXBALL_RUNTIME_CPP_TABLES_H
#define DXBALL_RUNTIME_CPP_TABLES_H
#include <stddef.h>

typedef struct DxBallCppPmd {
    int member_displacement, vbptr_displacement, virtual_displacement;
} DxBallCppPmd;
typedef struct DxBallCppTypePrefix {
    void *vtable, *cached_name;
    char name[1];
} DxBallCppTypePrefix;
typedef struct DxBallCppHandler {
    unsigned int adjectives;
    const DxBallCppTypePrefix *type;
    int catch_displacement;
    void (*handler)(void);
} DxBallCppHandler;
typedef struct DxBallCppTryEntry {
    int try_low, try_high, catch_high;
    unsigned int catch_count;
    const DxBallCppHandler *handlers;
} DxBallCppTryEntry;
/* Only the proven prefix is needed by these consumers. Pointer fields retain
   native width; unconsumed trailing metadata is not invented. */
typedef struct DxBallCppFunctionPrefix {
    unsigned int magic;
    int max_state;
    const void *unwind_map;
    unsigned int try_count;
    const DxBallCppTryEntry *try_map;
} DxBallCppFunctionPrefix;
/* Consumed exception-record prefix; no unobserved trailing fields. */
typedef struct DxBallCppExceptionRecord {
    unsigned int code;
} DxBallCppExceptionRecord;
typedef struct DxBallCppRegistration DxBallCppRegistration;
typedef struct DxBallCppContext DxBallCppContext;
typedef struct DxBallCppExceptionPointers {
    DxBallCppExceptionRecord *record;
    DxBallCppContext *context;
} DxBallCppExceptionPointers;
typedef struct DxBallCppCatchableType DxBallCppCatchableType;
/* Keep the original SDK pointer type at the translator ABI boundary. */
struct _EXCEPTION_POINTERS;
typedef void (*DxBallCppTranslator)(unsigned int, struct _EXCEPTION_POINTERS *);

#ifdef __cplusplus
extern DxBallCppTranslator __pSETranslator;
extern "C" {
void *dxball_cpp_adjust_pointer(void *object, const DxBallCppPmd &displacement);
int dxball_cpp_frame_unwind_filter(DxBallCppExceptionPointers *pointers);
const DxBallCppTryEntry *dxball_cpp_select_try_range(const DxBallCppFunctionPrefix *function,
    int nesting, int state, unsigned int *low, unsigned int *high);
void dxball_cpp_find_foreign_handler(DxBallCppExceptionRecord *exception,
    DxBallCppRegistration *registration, DxBallCppContext *context, void *dispatcher,
    const DxBallCppFunctionPrefix *function, int state, int nesting,
    DxBallCppRegistration *marker);

/* Genuine remaining translator, transfer and fatal boundaries. */
void dxball_cpp_inconsistency(void);
void dxball_cpp_terminate(void);
int dxball_cpp_call_se_translator(DxBallCppExceptionRecord *, DxBallCppRegistration *,
    void *, void *, const DxBallCppFunctionPrefix *, int, DxBallCppRegistration *);
void dxball_cpp_catch_it(DxBallCppExceptionRecord *, DxBallCppRegistration *,
    DxBallCppContext *, void *, const DxBallCppFunctionPrefix *, const DxBallCppHandler *,
    const DxBallCppCatchableType *, const DxBallCppTryEntry *, int, DxBallCppRegistration *);
}
#endif
#endif
