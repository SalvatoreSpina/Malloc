#include <strings.h>
#include <stdlib.h>

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char *addr1;

	addr1 = calloc(16, 1);
	strcpy(addr1, "Bonjours\n");
    show_alloc_mem();
	return (0);
}