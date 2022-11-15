#include "../includes/malloc.h"

pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *start_heap = NULL;