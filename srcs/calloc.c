#include "../includes/malloc.h"

// Return null if error occurs
// Else, malloc an area and then set it to 0
void *calloc_helper(size_t count, size_t size) {
    size_t total_size = count * size;
    void *pointer;

    if (!count || !size || (total_size / count != size))
        return NULL;
    if ((pointer = malloc_helper(total_size)))
        be_zero(pointer, total_size);
    return pointer;
}

/*
The calloc() function allocates memory for an array of nmemb
elements of size bytes each and returns a pointer to the
allocated memory.  The memory is set to zero.  If nmemb or size
is 0, then calloc() returns either NULL, or a unique pointer
value that can later be successfully passed to free().
*/
void *calloc(size_t count, size_t size) {
    void *pointer;

    pthread_mutex_lock(&malloc_mutex);
    pointer = calloc_helper(count, size);
    pthread_mutex_unlock(&malloc_mutex);
    return (pointer);
}