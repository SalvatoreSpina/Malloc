#include <strings.h>
#include <stdlib.h>

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char *addr1[1024];

    for (int i = 0; i < 64; i++)
        addr1[i] = malloc(16);

    for (int i = 0; i < 32; i++)
        free(addr1[i]);
    
    for (int i = 0; i < 16; i++)
        addr1[i] = malloc(32);

    show_alloc_mem();
	return (0);
}