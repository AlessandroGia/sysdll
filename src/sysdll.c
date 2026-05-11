#include <stdint.h>

#include "memory/mem.h"
#include "syscall.h"

#include "nsyscall/nsyscall.h"
#include "sysdll.h"

int32_t sysOpenProcess(uint32_t pid, int32_t mask, void **handle)
{
    uint32_t nsyscall = get_syscall_number_by_name((uint8_t *)"NtOpenProcess");

    __declspec(align(8)) uint8_t arg3[0x30] = {0};
    __declspec(align(8)) uint8_t arg4[0x10] = {0};

    write_u32(&arg3, 0x30);
    write_u64(&arg4, (uintptr_t)pid);

    return syscall4(
        (uintptr_t)handle,
        (uintptr_t)mask,
        (uintptr_t)&arg3,
        (uintptr_t)&arg4,
        nsyscall);
}

int32_t sysWriteVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *written)
{
    uint32_t nsyscall = get_syscall_number_by_name((uint8_t *)"NtWriteVirtualMemory");
    return syscall5(
        (uintptr_t)handle,
        (uintptr_t)addr,
        (uintptr_t)buffer,
        (uintptr_t)nsize,
        (uintptr_t)written,
        nsyscall);
}

int32_t sysReadVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *read)
{
    uint32_t nsyscall = get_syscall_number_by_name((uint8_t *)"NtReadVirtualMemory");
    return syscall5(
        (uintptr_t)handle,
        (uintptr_t)addr,
        (uintptr_t)buffer,
        (uintptr_t)nsize,
        (uintptr_t)read,
        nsyscall);
}
