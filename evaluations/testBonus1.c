#include <strings.h>
#include <stdlib.h>

int		main(void)
{
	char *addr1;

	addr1 = malloc(3000);
	for (int i = 0; i < 3000; i++)
		addr1[i] = 'A';
    show_alloc_mem_ex();
	return (0);
}