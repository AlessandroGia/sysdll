#include <stdint.h>

uint8_t read_u8(const void *addr);
uint16_t read_u16(const void *addr);
uint32_t read_u32(const void *addr);
uint64_t read_u64(const void *addr);

void write_u8(void *addr, uint8_t value);
void write_u16(void *addr, uint16_t value);
void write_u32(void *addr, uint32_t value);
void write_u64(void *addr, uint64_t value);
