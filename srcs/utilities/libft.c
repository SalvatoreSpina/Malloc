#include "../../includes/malloc.h"

void put_hexa(size_t n, char base, char len, boolean prefix) {
	char *str = "0123456789ABCDEF";
	if (n / base)
		put_hexa(n / base, base, len - 1, prefix);
	else {
		if (prefix)
			put_string("0x");
		while (--len > 0)
			write(1, "0", 1);
	}
	write(1, &str[n % base], 1);
}

static int str_len(char *str) {
	int i = 0;
	while (str[i])
		i++;
	return i;
}

void put_string(char *str) {
	write(1, str, str_len(str));
}

void mem_set(void *ptr, int value, size_t size) {
    unsigned char *ptr_char = (unsigned char *)ptr;
    while (size--)
        *ptr_char++ = (unsigned char) value;
}

void *mem_move(void *dst, const void *src, size_t len) {
	char *dst_str = (char *)dst;
	char *src_str = (char *)src;

	if (dst == src)
		return (dst);
	if (dst_str < src_str)
		return mem_cpy(dst_str, src_str, len);
	else
	{
		while (len--)
			dst_str[len] = src_str[len];
	}
	return (dst);
}

void *mem_cpy(void *dst, const void *src, size_t n) {
	char	*dst_str = (char *)dst;
	char	*src_str = (char *)src;

	if (dst == src)
		return (dst);
	while (n--)
		*dst_str++ = *src_str++;
	return (dst);
}

void be_zero(void *pointer, size_t size) {
    mem_set(pointer, 0, size);
}