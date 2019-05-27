#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "types.h"
#include "multiboot.h"

STATUS mem_mgr_init(multiboot_mmap_t* mmap_start, uint32_t mmap_length);
void* malloc(size_t size);
STATUS free(void* addr);
#ifdef __cplusplus
}
#endif
