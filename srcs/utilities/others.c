#include "../../includes/malloc.h"

// Search in the heap if a block is equal to the pointer
// If yes, ptr_heap and ptr_block are set there
void find_pointer(t_heap **ptr_heap, t_block **ptr_block, t_heap *start, void *pointer) {
    t_block *block_ptr;

    block_ptr = NULL;
    while (start) {
        block_ptr = (t_block *) JUMP_HEAP(start);
        while (block_ptr) {
            if (JUMP_BLOCK(block_ptr) == pointer) {
                *ptr_heap = start;
                *ptr_block = block_ptr;
                return;
            }
            block_ptr = block_ptr->next;
        }
        start = start->next;
    }
    *ptr_heap = NULL;
    *ptr_block = NULL;
}

// Return allocation type based on size
allocation_type get_type(const size_t size) {
    if (size > (size_t)SMALL_BLOCK_SIZE)
        return LARGE;
    else if (size > (size_t)TINY_BLOCK_SIZE)
        return SMALL;
    return TINY;
}

// Return the heap size based on type
size_t get_size(const size_t size) {
    allocation_type type = get_type(size);
    if (type == TINY)
        return (size_t)TINY_HEAP_SIZE;
    else if (type == SMALL)
        return (size_t)SMALL_HEAP_SIZE;
    else
        return size + sizeof(t_block) + sizeof(t_heap);
}