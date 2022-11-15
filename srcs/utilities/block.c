#include "../../includes/malloc.h"

// Block default constructor
void block_constructor(t_block *block, size_t size) {
	block->prev = NULL;
	block->next = NULL;
	block->size = size;
	block->free = FALSE;
}

// Return the last block in list
t_block *get_last_block(t_block *block) {
    while (block->next)
        block = block->next;
    return block;
}

// Remove a block if it's the last
void remove_if_last_block(t_heap *heap, t_block *block) {
    if (block->free && !block->next) {
        if (block->prev)
            block->prev->next = NULL;
        heap->free_size += block->size + sizeof(block);
        heap->block_count--;
    }
}

// Create a block, links in blocks list
static void divide_block(t_block *block, size_t size, t_heap *heap) {
    t_block *free_block;

    free_block = JUMP_BLOCK(block) + size;
    block_constructor(free_block, block->next - free_block);
    free_block->prev = block;
    free_block->next = block->next;
    free_block->free = TRUE;
    heap->block_count++;
    block->next = free_block;
    block->size = size;
    block->free = FALSE;
}

// Search in the heap if there's a block that can be used
// The block must be free and have enough space
static void find_block(size_t size, t_heap **ptr_heap, t_block **ptr_block) {
    t_heap *heap = start_heap;
    t_block *block;
    allocation_type type = get_type(size);

    while (heap) {
        block = (t_block *)JUMP_HEAP(heap);
        while (heap->type == type && block) {
            if (block->free && (block->size >= size + sizeof(block))) {
                *ptr_heap = heap;
                *ptr_block = block;
                return ;
            }
            block = block->next;
        }
        heap = heap->next;
    }
    *ptr_heap = NULL;
    *ptr_block = NULL;
}

// Try to find a block in the heap that can be used
// If yes, divide it and return the block
// If no, return NULL
t_block *try_fill(size_t size) {
    t_block *block;
    t_heap *heap;

    find_block(size, &heap, &block);
    if (block && heap) {
        divide_block(block, size, heap);
        return (block);
    }
    return NULL;
}

// If prev block is free, merge it with current block
static t_block *merge_previous(t_heap *heap, t_block *block) {
    if (heap && block && block->prev && block->prev->free) {
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
        block->prev->size += block->size + sizeof(block);
        heap->block_count--;
        return block->prev;
    }
    return NULL;
}

// If next block is free, merge it with current block
static void merge_next(t_heap *heap, t_block *block) {
    if (heap && block && block->next && block->next->free) {
        block->size += block->next->size + sizeof(block);
        if (block->next && block->next->next)
            block->next->next->prev = block;
        block->next = block->next->next;
        heap->block_count--;
    }
}

// Merge next, return merged prev
t_block *merge_blocks(t_heap *heap, t_block *block) {
    merge_next(heap, block);
    return merge_previous(heap, block);
}