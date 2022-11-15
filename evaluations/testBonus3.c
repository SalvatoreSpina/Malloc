#include <strings.h>
#include <stdlib.h>

void	print(char *s)
{
	write(1, s, strlen(s));
}

void test() {
    char *addr1;

    addr1 = malloc(128);
    addr1 = reallocf(addr1, NULL);
}

int		main(void)
{
    test();
    system("leaks testBonus3");
	return (0);
}