#ifndef MALLOC
#define MALLOC

#include <sys/mman.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

typedef enum	boolean {
    FALSE,
    TRUE
}				boolean;

typedef enum	allocation_type {
    TINY,
    SMALL,
    LARGE
}				allocation_type;

typedef struct heap {
    struct heap *prev;
    struct heap *next;
    allocation_type type;
    size_t total_size;
    size_t free_size;
    size_t block_count;
} t_heap;

typedef struct block {
    struct block *prev;
    struct block *next;
    size_t size;
    boolean free;
} t_block;

// Macros
# define JUMP_HEAP(start) ((void *)start + sizeof(t_heap))
# define JUMP_BLOCK(start) ((void *)start + sizeof(t_block))

// Supposing a pagesize of 4096 bytes
// TINY: block < 128 bytes
// SMALL: block < 1024 bytes
// LARGE: block > 1024 bytes

// For tiny, a preallocated heap of 16KB is used
// A block will be 128 bytes as maximum malloc
// That allows 128 blocks in the heap
// Less blocks will be realy available due to metadata size
# define TINY_HEAP_SIZE (4 * getpagesize())
# define TINY_BLOCK_SIZE (TINY_HEAP_SIZE / 128)

// For small, a preallocated heap of 128KB is used
// A block will be 1024 bytes as maximum malloc
# define SMALL_HEAP_SIZE (32 * getpagesize())
# define SMALL_BLOCK_SIZE (SMALL_HEAP_SIZE / 128)

// On MacOS, data is aligned on 16 bytes
# define ALIGN 15

// Globals
extern t_heap *start_heap;
extern pthread_mutex_t malloc_mutex;

// Library methods
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

// Bonus methods
void *calloc(size_t count, size_t size);
void *reallocf(void *ptr, size_t size);
void show_alloc_mem_ex();

// Internal functions
void block_constructor(t_block *block, size_t size);
t_block *get_last_block(t_block *block);
void remove_if_last_block(t_heap *heap, t_block *block);
t_block *try_fill(const size_t size);
t_block *merge_blocks(t_heap *heap, t_block *block);

t_heap *create_heap(allocation_type type, size_t block_size);
void *append_block(t_heap *heap, size_t size);
void delete_heap(t_heap *heap);
t_heap *get_heap(const t_heap *start, const allocation_type type, const size_t size);
t_heap *get_last_heap(t_heap *heap);
t_heap *find_heap(const size_t size);

void find_pointer(t_heap **ptr_heap, t_block **ptr_block, t_heap *start, void *pointer);
allocation_type get_type(const size_t size);
size_t get_size(const size_t size);

size_t print_blocks(t_block *block);
void show_alloc_mem_helper();
void print_heap_info(t_heap *heap);
void print_line(char *start);
void show_alloc_ex_helper();
void show_alloc_mem_ex();

void put_hexa(size_t n, char base, char len, boolean prefix);
void put_string(char *str);
void mem_set(void *ptr, int value, size_t len);
void *mem_move(void *dst, const void *src, size_t len);
void *mem_cpy(void *dst, const void *src, size_t n);
void be_zero(void *pointer, size_t size);

void *malloc_helper(size_t size);
void *calloc_helper(size_t count, size_t size);
void *realloc_helper(void *ptr, size_t size);
void *reallocf_helper(void *ptr, size_t size);
void free_helper(void *pointer);

#endif