#ifndef RAWSYS_SYSCALL_H
#define RAWSYS_SYSCALL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int32_t syscall0(
        uint32_t syscall_id);

    int32_t syscall1(
        uintptr_t arg1,
        uint32_t syscall_id);

    int32_t syscall2(
        uintptr_t arg1,
        uintptr_t arg2,
        uint32_t syscall_id);

    int32_t syscall3(
        uintptr_t arg1,
        uintptr_t arg2,
        uintptr_t arg3,
        uint32_t syscall_id);

    int32_t syscall4(
        uintptr_t arg1,
        uintptr_t arg2,
        uintptr_t arg3,
        uintptr_t arg4,
        uint32_t syscall_id);

    int32_t syscall5(
        uintptr_t arg1,
        uintptr_t arg2,
        uintptr_t arg3,
        uintptr_t arg4,
        uintptr_t arg5,
        uint32_t syscall_id);

    int32_t syscall6(
        uintptr_t arg1,
        uintptr_t arg2,
        uintptr_t arg3,
        uintptr_t arg4,
        uintptr_t arg5,
        uintptr_t arg6,
        uint32_t syscall_id);

#ifdef __cplusplus
}
#endif

#endif
