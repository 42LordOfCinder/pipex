NAME = libftprintf.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

INCLUDE = include

SRCS = srcs/ft_printf.c            \
	   srcs/ft_putchar_count.c     \
	   srcs/ft_putstr_count.c      \
	   srcs/ft_putnbr_count.c      \
	   srcs/ft_putnbr_base_count.c \
	   srcs/ft_putptr_count.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -I ./${INCLUDE} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

PHONY: all clean fclean re
