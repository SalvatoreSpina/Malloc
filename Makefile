ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PATH_OBJ = obj
PATH_SRC = srcs
SOURCES += globals.c malloc.c free.c realloc.c reallocf.c calloc.c show_alloc_mem.c show_alloc_mem_hex.c \
			utilities/block.c utilities/heap.c utilities/libft.c utilities/others.c

OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc -Wall -Wextra -Werror -fPIC -shared -Qunused-arguments

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) -o $@ $(OBJECTS)
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $(FLAGS_CC) $^ -O0 -g -I ./includes

clean:
	@rm -rf $(PATH_OBJ)

fclean: clean
	@rm -f $(NAME) $(LIB_NAME)
	@rm -f test0 test1 test2 test3 test4 test5 test6 testBonus1 testBonus2 testBonus3 testBonus4

re: fclean $(NAME)

zero:
	@make > /dev/null 2>&1
	@gcc -o test0 evaluations/test0.c > /dev/null 2>&1
	@bash run.sh /usr/bin/time -l ./test0

one:
	@make > /dev/null 2>&1
	@gcc -o test1 evaluations/test1.c > /dev/null 2>&1
	@bash run.sh /usr/bin/time -l ./test1

two:
	@make > /dev/null 2>&1
	@gcc -o test2 evaluations/test2.c > /dev/null 2>&1
	@bash run.sh /usr/bin/time -l ./test2

three:
	@make > /dev/null 2>&1
	@gcc -o test3 evaluations/test3.c > /dev/null 2>&1
	@bash run.sh /usr/bin/time -l ./test3

four:
	@make > /dev/null 2>&1
	@gcc -o test4 evaluations/test4.c > /dev/null 2>&1
	@bash run.sh /usr/bin/time -l ./test4

five:
	@make > /dev/null 2>&1
	@gcc -o test5 evaluations/test5.c > /dev/null 2>&1
	@bash run.sh /usr/bin/time -l ./test5

six:
	@make > /dev/null 2>&1
	@gcc -o test6 evaluations/test6.c -L. -lft_malloc > /dev/null 2>&1
	@/usr/bin/time -l ./test6

bone:
	@make > /dev/null 2>&1
	@gcc -o testBonus1 evaluations/testBonus1.c -L. -lft_malloc > /dev/null 2>&1
	@/usr/bin/time -l ./testBonus1

btwo:
	@make > /dev/null 2>&1
	@gcc -o testBonus2 evaluations/testBonus2.c -L. -lft_malloc > /dev/null 2>&1
	@/usr/bin/time -l ./testBonus2

bthree:
	@make > /dev/null 2>&1
	@gcc -o testBonus3 evaluations/testBonus3.c -L. -lft_malloc > /dev/null 2>&1
	@/usr/bin/time -l ./testBonus3

bfour:
	@make > /dev/null 2>&1
	@gcc -o testBonus4 evaluations/testBonus4.c -L. -lft_malloc > /dev/null 2>&1
	@/usr/bin/time -l ./testBonus4