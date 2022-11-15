#include "../../includes/malloc.h"

// Search in the linked list the first heap that has enough space and the right type
t_heap *get_heap(const t_heap *start, const allocation_type type, const size_t size) {
    t_heap *heap_ptr = (t_heap *) start;

    while (heap_ptr) {
        if ((heap_ptr->type == type) && (heap_ptr->free_size >= size))
            return heap_ptr;
        heap_ptr = heap_ptr->next;
    }
    return NULL;
}

// Find a heap with enough space using get_heap
// If there's no heap, create one
// If can't create one, return NULL
t_heap *find_heap(const size_t size) {
    t_heap *first_heap = start_heap;
    allocation_type type = get_type(size);
    t_heap *heap = get_heap(first_heap, type, size + sizeof(t_block));

    if (!heap) {
        if (!(heap = create_heap(type, size)))
            return NULL;
        heap->next = (t_heap *)first_heap;
        if (heap->next)
            heap->next->prev = heap;
        start_heap = heap;
    }
    return heap;
}

// https://man7.org/linux/man-pages/man2/getrlimit.2.html
// Check if the heap is too big
static rlim_t get_system_limit(void) {
	struct rlimit rpl;
	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
        return -1;
    return rpl.rlim_max;
}

// Create a new heap, using mmap
// Check if there's space with system limit
// Read: Pages may be read
// Write: Pages may be written
// Private: Create a private copy-on-write mapping. Not visible out of process
// Anonymous: Don't use a file
// https://man7.org/linux/man-pages/man2/mmap.2.html
t_heap *create_heap(allocation_type type, size_t block_size)
{
	size_t	heap_size = get_size(block_size);
	t_heap	*heap;

	if (heap_size > get_system_limit())
		return (NULL);
	heap = (t_heap *)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (heap == MAP_FAILED)
		return (NULL);
	be_zero(heap, sizeof(heap));
	heap->type = type;
	heap->total_size = heap_size;
	heap->free_size = heap_size - sizeof(t_heap);
	return heap;
}

// Create a block where possible, links and return it
void *append_block(t_heap *heap, size_t size) {
    t_block *new_block = (t_block *) JUMP_HEAP(heap);
    t_block *last_block = NULL;

    if (heap->block_count) {
        last_block = get_last_block(new_block);
        new_block = (t_block *)(JUMP_BLOCK(last_block) + last_block->size);
    }
    block_constructor(new_block, size);
    if (heap->block_count) {
        last_block->next = new_block;
        new_block->prev = last_block;
    }
    heap->block_count++;
    heap->free_size -= (new_block->size + sizeof(t_block));
    return (void *)JUMP_BLOCK(new_block);
}

// Return true if there's only one heap of allocation type
static boolean last_heap(t_heap *heap) {
    t_heap *heap_ptr;
    allocation_type type;
    int i = 0;

    heap_ptr = start_heap;
    if ((type = heap->type) == LARGE)
        return FALSE;
    while (heap_ptr) {
        if (heap_ptr->type == type)
            i++;
        heap_ptr = heap_ptr->next;
    }
    return (i == 1);
}

t_heap *get_last_heap(t_heap *heap) {
	if (!heap)
		return NULL;
	while (heap->next)
		heap = heap->next;
	return heap;
}

// Delete a heap if it's empty and not the last one
void delete_heap(t_heap *heap) {
    if (heap->block_count)
        return;
    if (heap->prev)
        heap->prev->next = heap->next;
    if (heap->next)
        heap->next->prev = heap->prev;
    if (!last_heap(heap)) {
        if (heap == start_heap)
            start_heap = heap->next;
        munmap(heap, heap->total_size);
    }
}