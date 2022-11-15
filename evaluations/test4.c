#include <strings.h>
#include <stdlib.h>

#define M 1024 * 1024

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = malloc(16 * M);
	addr3 = realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}
