#include "runtime_signals.h"

DxBallCrtSignalState dxball_crt_signal_state = {
    {
        {0xc0000005UL, 11, {0}},
        {0xc000001dUL, 4, {0}},
        {0xc0000096UL, 4, {0}},
        {0xc000008dUL, 8, {0}},
        {0xc000008eUL, 8, {0}},
        {0xc000008fUL, 8, {0}},
        {0xc0000090UL, 8, {0}},
        {0xc0000091UL, 8, {0}},
        {0xc0000092UL, 8, {0}},
        {0xc0000093UL, 8, {0}}
    },
    3, 7, 10, 140, 0
};

static DxBallCrtSignalAction control_c;
static DxBallCrtSignalAction control_break;
static DxBallCrtSignalAction abort_action;
static DxBallCrtSignalAction terminate_action;

/* FUNCTION: DXBALL 0x0041F450 */
DxBallCrtSignalRecord *dxball_crt_siglookup(int signal_number)
{
    unsigned char *cursor = (unsigned char *)&dxball_crt_signal_state;
    do {
        if (((const DxBallCrtSignalProbe *)cursor)->signal_number == signal_number) break;
        cursor += sizeof(DxBallCrtSignalRecord);
    } while (cursor < (unsigned char *)&dxball_crt_signal_state +
             dxball_crt_signal_state.record_count * sizeof(DxBallCrtSignalRecord));
    return ((const DxBallCrtSignalProbe *)cursor)->signal_number == signal_number
        ? (DxBallCrtSignalRecord *)cursor : 0;
}

/* FUNCTION: DXBALL 0x0041BEC0 */
DxBallCrtSignalRecord *dxball_crt_exception_lookup(DxBallCrtDword exception_code)
{
    unsigned char *cursor = (unsigned char *)&dxball_crt_signal_state;
    do {
        if (((const DxBallCrtSignalProbe *)cursor)->exception_code == exception_code) break;
        cursor += sizeof(DxBallCrtSignalRecord);
    } while (cursor < (unsigned char *)&dxball_crt_signal_state +
             dxball_crt_signal_state.record_count * sizeof(DxBallCrtSignalRecord));
    return ((const DxBallCrtSignalProbe *)cursor)->exception_code == exception_code
        ? (DxBallCrtSignalRecord *)cursor : 0;
}

/* FUNCTION: DXBALL 0x0041F2C0 */
int dxball_crt_raise(int signal_number)
{
    DxBallCrtSignalAction *slot;
    DxBallCrtSignalAction handler;
    int index;
    switch (signal_number) {
    case 2: slot = &control_c; handler = control_c; break;
    case 4:
    case 8:
    case 11:
        slot = &dxball_crt_siglookup(signal_number)->action;
        handler = *slot;
        break;
    case 15: slot = &terminate_action; handler = terminate_action; break;
    case 21: slot = &control_break; handler = control_break; break;
    case 22: slot = &abort_action; handler = abort_action; break;
    default: return -1;
    }
    if (handler.tag == 1) return 0;
    if (handler.tag == 0) dxball_crt_quick_exit(3);
    if (signal_number == 8 || signal_number == 11 || signal_number == 4) {
        DxBallCrtExceptionPointers *saved_information = dxball_crt_signal_state.information;
        dxball_crt_signal_state.information = 0;
        if (signal_number == 8) {
            int saved_floating = dxball_crt_signal_state.floating_code;
            dxball_crt_signal_state.floating_code = 140;
            for (index = dxball_crt_signal_state.first_floating;
                 index < dxball_crt_signal_state.first_floating + dxball_crt_signal_state.floating_count;
                 ++index)
                dxball_crt_signal_state.records[index].action.tag = 0;
            handler.floating(8, dxball_crt_signal_state.floating_code);
            dxball_crt_signal_state.information = saved_information;
            dxball_crt_signal_state.floating_code = saved_floating;
        } else {
            slot->tag = 0;
            handler.simple(signal_number);
            dxball_crt_signal_state.information = saved_information;
        }
    } else {
        slot->tag = 0;
        handler.simple(signal_number);
    }
    return 0;
}

/* FUNCTION: DXBALL 0x0041BD60 */
int dxball_crt_exception_filter(DxBallCrtDword exception_code,
                                DxBallCrtExceptionPointers *information)
{
    DxBallCrtSignalRecord *record = dxball_crt_exception_lookup(exception_code);
    size_t handler;
    DxBallCrtExceptionPointers *saved_information;
    int saved_floating;
    if (record == 0) goto unhandled;
    handler = record->action.tag;
    if (handler == 0) goto unhandled;
    if (handler == 5) {
        record->action.tag = 0;
        return 1;
    }
    if (handler == 1) return -1;
    saved_information = dxball_crt_signal_state.information;
    dxball_crt_signal_state.information = information;
    if (record->signal_number == 8) {
        int first = dxball_crt_signal_state.first_floating;
        if (first < dxball_crt_signal_state.first_floating + dxball_crt_signal_state.floating_count) {
            unsigned char *cursor = (unsigned char *)&dxball_crt_signal_state +
                first * sizeof(DxBallCrtSignalRecord) + offsetof(DxBallCrtSignalRecord, action);
            int remaining = dxball_crt_signal_state.floating_count;
            do {
                ((DxBallCrtSignalAction *)(void *)cursor)->tag = 0;
                cursor += sizeof(DxBallCrtSignalRecord);
            } while (--remaining != 0);
        }
        saved_floating = dxball_crt_signal_state.floating_code;
        if (record->exception_code == 0xc000008eUL) dxball_crt_signal_state.floating_code = 131;
        else if (record->exception_code == 0xc0000090UL) dxball_crt_signal_state.floating_code = 129;
        else if (record->exception_code == 0xc0000091UL) dxball_crt_signal_state.floating_code = 132;
        else if (record->exception_code == 0xc0000093UL) dxball_crt_signal_state.floating_code = 133;
        else if (record->exception_code == 0xc000008dUL) dxball_crt_signal_state.floating_code = 130;
        else if (record->exception_code == 0xc000008fUL) dxball_crt_signal_state.floating_code = 134;
        else if (record->exception_code == 0xc0000092UL) dxball_crt_signal_state.floating_code = 138;
        ((DxBallCrtFloatingHandler)handler)(8, dxball_crt_signal_state.floating_code);
        dxball_crt_signal_state.floating_code = saved_floating;
    } else {
        record->action.tag = 0;
        ((DxBallCrtSignalHandler)handler)(record->signal_number);
    }
    dxball_crt_signal_state.information = saved_information;
    return -1;
unhandled:
    return (int)UnhandledExceptionFilter(information);
}
