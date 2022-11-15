#include "../includes/malloc.h"

// Basically manage errors like the man said to do
// Find the pointer, chekc size and mem_move what's needed
void *realloc_helper(void *pointer, size_t size) {
    t_heap *heap;
    t_block *block;
    void *new_pointer;

    if (!pointer)
        return malloc_helper(size);
    if (!size) {
        free_helper(pointer);
        return NULL;
    }
    heap = start_heap;
    find_pointer(&heap, &block, heap, pointer);
    if (!block || !heap)
        return NULL;
    else if (block->size == size)
        return pointer;
    new_pointer = malloc_helper(size);
    mem_move(new_pointer, pointer, block->size > size ? size : block->size);
    free_helper(pointer);
    return new_pointer;
}

/*
The realloc() function changes the size of the memory block
pointed to by ptr to size bytes.  The contents will be unchanged
in the range from the start of the region up to the minimum of
the old and new sizes.  If the new size is larger than the old
size, the added memory will not be initialized.  If ptr is NULL,
then the call is equivalent to malloc(size), for all values of
size; if size is equal to zero, and ptr is not NULL, then the
call is equivalent to free(ptr).
*/
void *realloc(void *pointer, size_t size) {
    void *result;

    pthread_mutex_lock(&malloc_mutex);
    result = realloc_helper(pointer, size);
    pthread_mutex_unlock(&malloc_mutex);

    return (result);
}