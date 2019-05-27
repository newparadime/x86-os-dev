#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

typedef struct mblock_info_s
{
    bool free:1;
    bool corrupt:1;
    bool supervisor:1;
    bool contig:1;
} __attribute__((packed)) mblock_info_t;

/* Linked list node describing a block of memory */
/* Points to previous element in the list, since */
/*  we only will ever be adding a block to, or   */
/*  removing a block from, the end of the list.  */
//typedef struct mblock_s mblock_t;
typedef struct mblock_s
{
    struct mblock_s* prev;
    size_t size;
    mblock_info_t info;
    char __attribute__((aligned(sizeof(void*)))) data[];
} mblock_t;

typedef struct mblock_list_s
{
    mblock_t* head;
} mblock_list_t;

STATUS mblock_list_append(mblock_list_t* list, mblock_t* mblock);
mblock_t* mblock_list_pop(mblock_list_t* list);

#ifdef __cplusplus
}
#endif
