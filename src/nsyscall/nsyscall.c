#include <stdint.h>

#include "nsyscall/nsyscall.h"
#include "nsyscall/peb.h"

#include "memory/mem.h"

static const uint8_t syscall_pattern[4] = {0x4C, 0x8B, 0xD1, 0xB8};

static void *ntdll_base = NULL;

static uint32_t *funcs = NULL;
static uint32_t *names = NULL;
static uint16_t *ordinals = NULL;

static uint32_t num_funcs = 0;

static void *get_data_directory()
{

    uint32_t e_lfanew = read_u32((uint8_t *)ntdll_base + 0x3C);
    uint8_t *nt_headers = (uint8_t *)ntdll_base + e_lfanew;
    uint8_t *file_header = nt_headers + 0x04;
    uint8_t *optional_header = file_header + 0x14;
    uint8_t *export_data_directory = optional_header + 0x70;

    return (void *)export_data_directory;
}

static void *get_export_table(void *data_directory)
{
    uint32_t rva = read_u32((uint8_t *)data_directory + 0x00);
    return (void *)((uint8_t *)ntdll_base + rva);
}

static uint32_t check_syscall(void *address)
{

    uint8_t *entry = (uint8_t *)address;
    for (int i = 0; i < 4; i++)
    {
        if (entry[i] != syscall_pattern[i])
            return 0;
    }
    return read_u32((uint8_t *)address + 0x4);
}

static uint8_t check_ntdll(wchar_t *dll_name)
{
    const wchar_t *target = L"ntdll.dll";
    uint16_t i = 0;
    while (target[i] != L'\0')
    {
        if (dll_name[i] != target[i])
            return 0;
        i++;
    }
    return dll_name[i] == L'\0';
}

static void *get_ntdll_base(void *peb)
{

    uint8_t *ldr = (uint8_t *)read_u64((uint8_t *)peb + 0x18);
    uint8_t *list_head = ldr + 0x10;
    uint8_t *entry = (uint8_t *)read_u64(list_head);

    while (entry != list_head)
    {
        wchar_t *base_name_buf = (wchar_t *)read_u64(entry + 0x60);

        if (check_ntdll(base_name_buf))
            return (void *)read_u64(entry + 0x30);

        entry = (uint8_t *)read_u64(entry + 0x00);
    }

    return 0x0;
}

static void init()
{
    void *peb = get_current_peb();
    ntdll_base = get_ntdll_base(peb);

    if (ntdll_base)
    {
        void *ntdll_data_directory = get_data_directory();
        void *ntdll_export_table = get_export_table(ntdll_data_directory);

        num_funcs = read_u32((uint8_t *)ntdll_export_table + 0x18);

        funcs = (uint32_t *)((uint8_t *)ntdll_base + read_u32((uint8_t *)ntdll_export_table + 0x1C));
        names = (uint32_t *)((uint8_t *)ntdll_base + read_u32((uint8_t *)ntdll_export_table + 0x20));
        ordinals = (uint16_t *)((uint8_t *)ntdll_base + read_u32((uint8_t *)ntdll_export_table + 0x24));
    }
}

static uint8_t compare_names(uint8_t *name1, uint8_t *name2)
{

    while (*name1 != '\0' && *name2 != '\0')
    {
        if (*name1 != *name2)
            break;
        name1++;
        name2++;
    }
    if (*name1 == '\0' && *name2 == '\0')
        return 1;
    return 0;
}

uint32_t get_syscall_number_by_name(uint8_t *name_sys)
{
    if (!funcs || !names || !ordinals || !num_funcs)
        init();
    if (!funcs || !names || !ordinals || !num_funcs)
        return 0xFFFFFFFF;

    void *name_nt = NULL;
    void *func_nt = NULL;
    uint32_t syscall_n = 0;
    uint32_t num = num_funcs;

    while (num--)
    {
        name_nt = (uint8_t *)ntdll_base + names[num];

        if (!compare_names(name_sys, name_nt))
            continue;

        func_nt = (uint8_t *)ntdll_base + funcs[ordinals[num]];
        syscall_n = check_syscall(func_nt);

        if (syscall_n)
            return syscall_n;
    }
    return 0;
}
