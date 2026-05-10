#include <stdio.h>
#include <stdint.h>

#include "memory/mem.h"
#include "syscall.h"

#include "nsyscall/nsyscall.h"
#include "sysdll.h"
#include "sys_structs.h"

void sysOpenProcess(uint32_t pid, int32_t mask, void **handle)
{

    uint32_t nsyscall = get_syscall_number_by_name((uint8_t *)"NtOpenProcess");

    sysOpenProcessARG3 arg3 = {0};
    sysOpenProcessARG4 arg4 = {0};

    write_u32(&arg3, sizeof(arg3));
    write_u64(&arg4, (uintptr_t)pid);

    syscall4(
        (uintptr_t)handle,
        (uintptr_t)mask,
        (uintptr_t)&arg3,
        (uintptr_t)&arg4,
        nsyscall);
}

void sysWriteVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *written)
{
    syscall5(
        (uintptr_t)handle,
        (uintptr_t)addr,
        (uintptr_t)buffer,
        (uintptr_t)nsize,
        (uintptr_t)written,
        0x3a);
}

void sysReadVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *read)
{
    syscall5(
        (uintptr_t)handle,
        (uintptr_t)addr,
        (uintptr_t)buffer,
        (uintptr_t)nsize,
        (uintptr_t)read,
        0x3f);
}
