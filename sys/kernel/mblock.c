#include "types.h"
#include "mblock.h"

/* Appends new mblock linked list node to mblock list beginning */
/*   at head. */
/* Returns pointer to head of list */
STATUS mblock_list_append(mblock_list_t* list, mblock_t* mblock)
{
    if(list && mblock)
    {
        /* Set prev pointer of new mblock to current head of list */
        mblock->prev = list->head;
        /* Set head of list to new block */
        list->head = mblock;
        return OK;    
    }
    else
    {
        return SYSERR;
    }
}

/* Removes the last element in the list pointed to by head, */
/*   sets head to the previous element, and returns the     */
/*   detached mblock. Logic inherently returns NULL by if   */
/*   list is empty (list->head == NULL). */
/* If list doesn't point to a valid structure, returns NULL */
mblock_t* mblock_list_pop(mblock_list_t* list)
{
    mblock_t* mblock = NULL;
    /* If list points to a valid structure... */
    if (list)
    {
        /* Initialize mblock to head */
        mblock = list->head;
        /* If mblock now points to an valid block */
        if (mblock)
        {
            list->head = mblock->prev;
        }
        /* Otherwise, mblock already points to NULL */
        /*  and we can just return it as-is */
    }
    return mblock;
}
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
