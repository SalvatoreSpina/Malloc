#include "../includes/malloc.h"

// Print type
static void print_type(t_heap *heap)
{
	if (heap->type == TINY)
		put_string("TINY");
	else if (heap->type == SMALL)
		put_string("SMALL");
	else
		put_string("LARGE");
}

// Print heap infos
void print_heap_info(t_heap *heap) {
    print_type(heap);
    put_string(" - ");
    put_hexa((size_t)heap, 16, 0, TRUE);
    put_string("\n");
}

// Print in hexa the memory of the heap
void print_line(char *start) {
    size_t i = 0;

    put_hexa((size_t)start, 16, 0, TRUE);
    while (i < 16) {
        put_string(" ");
        put_hexa((size_t)start[i], 16, 2, FALSE);
        i++;
    }
    put_string("\n");
}

// For every heap, print the heap info and the blocks
void show_alloc_ex_helper(void) {
    t_heap *heap = start_heap;
    size_t i;
    char *pointer;

    while (heap) {
        print_heap_info(heap);
        i = 0;
        pointer = (char *)heap;
        while (i < heap->total_size) {
            print_line(pointer + i);
            i += 16;
        }
        heap = heap->next;
    }
}

// The show_alloc_mem_ex() function displays the allocated memory in hexadecimal
void show_alloc_mem_ex(void) {
	pthread_mutex_lock(&malloc_mutex);
	show_alloc_ex_helper();
	pthread_mutex_unlock(&malloc_mutex);
}
