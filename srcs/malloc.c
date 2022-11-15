#include "../includes/malloc.h"

// If there's no size, return NULL
// Try to fill the available heap
// If there's no heap, get / create one
// Then, appends a block in it
void *malloc_helper(size_t size) {
    t_heap *heap;
    t_block *block;
    void *pointer;

    if (!size)
        return NULL;
    size = (size + ALIGN) & ~ALIGN;
    if ((block = try_fill(size)))
        return JUMP_BLOCK(block);
    if (!(heap = find_heap((const size_t) size)))
        return NULL;
    pointer = append_block(heap, size);
    return pointer;
}

/*
The malloc() function allocates size bytes and returns a pointer
to the allocated memory.  The memory is not initialized.  If size
is 0, then malloc() returns either NULL, or a unique pointer
value that can later be successfully passed to free().
*/
void *malloc(size_t size) {
    void *pointer;

    pthread_mutex_lock(&malloc_mutex);
    pointer = malloc_helper(size);
    pthread_mutex_unlock(&malloc_mutex);
    return (pointer);
}