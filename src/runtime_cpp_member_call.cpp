#include "runtime_cpp_object.h"
#include "runtime_memory_copy.h"

/* The original API carries direct method addresses and an already adjusted
   object. Microsoft x86 single-inheritance member pointers use that address. */
struct DxBallCppMemberTarget {};
typedef void (DxBallCppMemberTarget::*DxBallCppMember0)();
typedef void (DxBallCppMemberTarget::*DxBallCppMember1)(void *);
typedef void (DxBallCppMemberTarget::*DxBallCppMember2)(void *, int);
typedef char DxBallCppMemberAddressesMustBeDirect[
    sizeof(void *) == 4 && sizeof(DxBallCppMember0) == sizeof(void *) &&
    sizeof(DxBallCppMember1) == sizeof(void *) &&
    sizeof(DxBallCppMember2) == sizeof(void *) ? 1 : -1];

/* FUNCTION: DXBALL 0x004184E0 */
void DXBALL_CPP_STDCALL _CallMemberFunction0(void *object, void *code)
{
    DxBallCppMember0 member;
    dxball_crt_memcpy(&member, &code, sizeof(member));
    (static_cast<DxBallCppMemberTarget *>(object)->*member)();
}

/* FUNCTION: DXBALL 0x004184F0 */
void DXBALL_CPP_STDCALL _CallMemberFunction1(void *object, void *code,
                                           void *argument)
{
    DxBallCppMember1 member;
    dxball_crt_memcpy(&member, &code, sizeof(member));
    (static_cast<DxBallCppMemberTarget *>(object)->*member)(argument);
}

/* FUNCTION: DXBALL 0x00418500 */
void DXBALL_CPP_STDCALL _CallMemberFunction2(void *object, void *code,
                                           void *argument, int virtual_base)
{
    DxBallCppMember2 member;
    dxball_crt_memcpy(&member, &code, sizeof(member));
    (static_cast<DxBallCppMemberTarget *>(object)->*member)(argument, virtual_base);
}
