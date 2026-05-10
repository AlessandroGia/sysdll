#include <stdint.h>

void sysOpenProcess(uint32_t pid, int32_t mask, void **handle);
void sysWriteVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *written);
void sysReadVirtualMemory(void *handle, void *addr, void *buffer, size_t nsize, size_t *read);
