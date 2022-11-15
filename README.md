# Malloc

We do know Malloc, right? But do we really know it?

My personal implementation of Malloc. It creates the shared library libft_malloc.so which can replace malloc in any system commands.

## Why?

When I code, I like to know what's going on behind the scenes. Malloc is one of the most important function of C, so why not re-implement it?

### Structure

Basically, we preallocate memory using mmap. That will be a t_heap structure. They are stored in a doubly linked list so that multiple heaps can be used. That allow us to use different heaps to manage different size of allocations.

```c
typedef struct heap {
    struct heap *prev;
    struct heap *next;
    allocation_type type;
    size_t total_size;
    size_t free_size;
    size_t block_count;
} t_heap;
```

The heap size is calculated to be able to store ~100 blocks of **Allocation Type**, this allow us to minimize the call of mmap.

```c
typedef struct block {
    struct block *prev;
    struct block *next;
    size_t size;
    boolean free;
} t_block;
```

### How it works?

The idea is simple: three type of allocation (tiny, small, large). The first two are managed by a heap. Every call to Malloc try to fill the already available heaps before creating a new one. The large allocation is managed by mmap directly. When free, the blocks are merged if possible so that the memory is succesfully defragmented. The presence of a Mutex allow the malloc to be thread safe.
