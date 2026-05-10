#include <stdint.h>

const uint8_t syscall_pattern[4] = {0x4C, 0x8B, 0xD1, 0xB8};

typedef struct Stub
{
    uint8_t *name;
    uint32_t syscall_number;
    struct Stub *next;
} Stub;
