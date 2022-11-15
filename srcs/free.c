#include "../includes/malloc.h"

// Return null if no pointer or heap
// Find the pointer, then set his status to free
// Merge blocks if possible and delete heap if empty
void free_helper(void *pointer) {
    t_heap *heap = start_heap;
    t_block *block;
    t_block *ret;

    if (!(pointer) || !(heap))
        return;
    find_pointer(&heap, &block, heap, pointer);
    if (block && heap) {
        block->free = TRUE;
        if ((ret = merge_blocks(heap, block)))
            block = ret;
        remove_if_last_block(heap, block);
        delete_heap(heap);
    }
}

/*
The free() function frees the memory space pointed to by ptr,
which must have been returned by a previous call to malloc(),
calloc(), or realloc().
*/
void free(void *pointer) {
    pthread_mutex_lock(&malloc_mutex);
    free_helper(pointer);
    pthread_mutex_unlock(&malloc_mutex);
}