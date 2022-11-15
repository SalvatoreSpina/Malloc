#include "../includes/malloc.h"

// The reallocf() function is identical to realloc()
// except that it will free the passed pointer when
// the requested memory cannot be allocated.
void *reallocf_helper(void *pointer, size_t size) {
    void *result = realloc_helper(pointer, size);
    if (!(result) && (size > 0))
        free_helper(pointer);
    return result;
}

void *reallocf(void *pointer, size_t size) {
    void *result;

    pthread_mutex_lock(&malloc_mutex);
    result = reallocf_helper(pointer, size);
    pthread_mutex_unlock(&malloc_mutex);
    return result;
}