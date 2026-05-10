#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "nsyscall/syscall_list.h"
#include "nsyscall/nsyscall.h"
#include "nsyscall/peb.h"

static void *get_data_directory(void *image_base)
{

    uint32_t e_lfanew = read_u32((uint8_t *)image_base + 0x3C);
    uint8_t *nt_headers = (uint8_t *)image_base + e_lfanew;
    uint8_t *file_header = nt_headers + 0x04;
    uint8_t *optional_header = file_header + 0x14;
    uint8_t *export_data_directory = optional_header + 0x70;

    return (void *)export_data_directory;
}

static void *get_export_table(void *base, void *data_directory)
{
    uint32_t rva = read_u32((uint8_t *)data_directory + 0x00);
    return (void *)((uint8_t *)base + rva);
}

static void *get_import_table(void *base, void *data_directory)
{
    uint32_t rva = read_u32((uint8_t *)data_directory + 0x08);
    return (void *)((uint8_t *)base + rva);
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

Stub *nsyscall()
{

    void *peb = get_current_peb();
    void *base = (void *)read_u64((uint8_t *)peb + 0x10);
    void *ntdll_base = get_ntdll_base(peb);

    void *ntdll_data_directory = get_data_directory(ntdll_base);
    void *ntdll_export_table = get_export_table(ntdll_base, ntdll_data_directory);

    Stub *head = NULL, *new = NULL, *this = NULL;
    uint32_t syscall_n = 0;

    uint32_t num_funcs = read_u32((uint8_t *)ntdll_export_table + 0x14);
    uint32_t num_names = read_u32((uint8_t *)ntdll_export_table + 0x18);

    uint32_t *funcs = (uint32_t *)((uint8_t *)base + read_u32((uint8_t *)ntdll_export_table + 0x1C));
    uint32_t *names = (uint32_t *)((uint8_t *)base + read_u32((uint8_t *)ntdll_export_table + 0x20));
    uint16_t *ordinals = (uint16_t *)((uint8_t *)base + read_u32((uint8_t *)ntdll_export_table + 0x24));

    void *name = NULL;
    void *func = NULL;

    for (int i = 0; i < num_names; i++)
    {

        func = (uint8_t *)base + funcs[ordinals[i]];

        if (syscall_n = check_syscall(func))
        {
            name = (uint8_t *)base + names[i];

            new = (Stub *)malloc(sizeof(Stub));
            new->name = name;
            new->syscall_number = syscall_n;
            new->next = NULL;

            if (!head)
                head = new;
            else
                this->next = new;
            this = new;
        }
    }

    return head;
}
