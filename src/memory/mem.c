#include <stdint.h>

#include "memory/mem.h"

static uint64_t read_bytes(const void *addr, size_t n)
{
    const uint8_t *_addr = (const uint8_t *)addr;
    uint64_t ret = 0;

    for (int i = 0; i < n; i++)
        ret |= ((uint64_t)_addr[i]) << (8 * i);
    return ret;
}

static void copy_bytes(void *dst, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
}

uint8_t read_u8(const void *addr)
{
    return (uint8_t)read_bytes(addr, 1);
}

uint16_t read_u16(const void *addr)
{
    return (uint16_t)read_bytes(addr, 2);
}

uint32_t read_u32(const void *addr)
{
    return (uint32_t)read_bytes(addr, 4);
}

uint64_t read_u64(const void *addr)
{
    return (uint64_t)read_bytes(addr, 8);
}

void write_u8(void *addr, uint8_t value)
{
    copy_bytes((uint8_t *)addr, &value, sizeof(value));
}

void write_u16(void *addr, uint16_t value)
{
    copy_bytes((uint16_t *)addr, &value, sizeof(value));
}

void write_u32(void *addr, uint32_t value)
{
    copy_bytes((uint32_t *)addr, &value, sizeof(value));
}

void write_u64(void *addr, uint64_t value)
{
    copy_bytes((uint64_t *)addr, &value, sizeof(value));
}

void zero(void *ptr, size_t size)
{
    uint8_t *p = (uint8_t *)ptr;

    for (size_t i = 0; i < size; i++)
    {
        p[i] = 0;
    }
}
