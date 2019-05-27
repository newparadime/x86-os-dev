#include "mem_mgr.h"
#include "mblock.h"
#include "types.h"

/* Pointer to head of memory map provided by multiboot bootloader */
static mblock_list_t mblock_list_free, mblock_list_alloc;

static inline multiboot_mmap_t* multiboot_mmap_next(multiboot_mmap_t* mmap)
{
     return (multiboot_mmap_t*)((uint32_t)mmap+mmap->size+sizeof(mmap->size));
} 
             
STATUS mem_mgr_init(multiboot_mmap_t* mmap_start, uint32_t mmap_length)
{
    for(multiboot_mmap_t* i = mmap_start;
          i < (multiboot_mmap_t*)((uint32_t)mmap_start+mmap_length);
             i = multiboot_mmap_next(i))
    {
        if(i->type == MULTIBOOT_MEMORY_AVAILABLE || i->type == MULTIBOOT_MEMORY_ACPI_RECLAIMABLE)
        {
            mblock_t* mblock = (mblock_t*)(uint32_t)i->addr;
            mblock->size = i->len;
            mblock->info = (mblock_info_t){ true, false, true, false };
            mblock_list_append(&mblock_list_free, mblock);
        }
    }
    if(mblock_list_free.head) return OK;
    return SYSERR;
}

void* malloc(size_t size)
{
    mblock_t* mblock = NULL;
    
    if(mblock_list_free.head->size >= size)
    {
        mblock = mblock_list_pop(&mblock_list_free);
    }
    else
    {
        mblock_t* entry = mblock_list_free.head;
        while(entry->prev && entry->prev->size < size)
        {
            entry = entry->prev;
        }
        mblock = entry->prev;
        if(mblock)
        {
            entry->prev = entry->prev->prev;
        }
    }
    
    if(mblock)
    {
        mblock->info.free = false;
        mblock_list_append(&mblock_list_alloc, mblock);
        return mblock->data;
    }
    
    return NULL;
}

STATUS free(void* addr)
{
    mblock_t* mblock = NULL;
    if(mblock_list_alloc.head->data == addr)
    {
        mblock = mblock_list_pop(&mblock_list_alloc);
    }
    else
    {
        mblock_t* entry = mblock_list_alloc.head;
        while(entry->prev && entry->prev->data != addr)
        {
            entry = entry->prev;
        }
        mblock = entry->prev;
        if(mblock)
        {
            entry->prev = entry->prev->prev;
        }
    }
    
    if(mblock)
    {
        mblock->info.free = true;
        mblock_list_append(&mblock_list_free, mblock);
        return OK;
    }
    return SYSERR;
}






















