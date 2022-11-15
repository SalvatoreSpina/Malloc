#include "../includes/malloc.h"

// Print every blocks, his range and size
size_t print_blocks(t_block *block) {
    char *start = NULL;
    char *end = NULL;
    size_t total = 0;

    while (block) {
        start = (char *)JUMP_BLOCK(block);
        end = start + block->size;
        if (!(block->free)) {
            put_hexa((size_t)start, 16, 9, TRUE);
            put_string(" - ");
            put_hexa((size_t)end, 16, 9, TRUE);
            put_string(" : ");
            put_hexa(block->size, 10, 0, FALSE);
            put_string(" bytes\n");
            total += block->size;
        }
        block = block->next;
    }
    return total;
}

// Print the tpye
void print_type(char *name, t_heap *heap)
{
    put_string(name);
    put_string(" : ");
    put_hexa((size_t)heap, 16, 9, TRUE);
    put_string("\n");
}

// Print each heap, it's type and size
void show_alloc_mem_helper(void) {
    t_heap *first_heap = start_heap;
    t_heap *last_heap = get_last_heap(first_heap);
    size_t total = 0;

    while (last_heap) {
        if (last_heap->type == TINY)
            print_type("TINY", last_heap);
        else if (last_heap->type == SMALL)
            print_type("SMALL", last_heap);
        else
            print_type("LARGE", last_heap);
        if (last_heap->block_count)
            total += print_blocks((t_block *)JUMP_HEAP(last_heap));
        last_heap = last_heap->prev;
    }
    put_string("Total : ");
    put_hexa(total, 10, 0, FALSE);
    put_string(" bytes\n"); 
}

// Show allocated memory
void show_alloc_mem(void) {
    pthread_mutex_lock(&malloc_mutex);
    show_alloc_mem_helper();
    pthread_mutex_unlock(&malloc_mutex);
}