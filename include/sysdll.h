#include <stdint.h>

int32_t sysOpenProcess(uint32_t pid, int32_t mask, void **handle);
int32_t sysWriteVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *written);
int32_t sysReadVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *read);
