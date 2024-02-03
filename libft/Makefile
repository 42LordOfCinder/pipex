SHELL = bash

NAME = libft.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c         \
	   ft_bzero.c        \
	   ft_calloc.c       \
	   ft_isalnum.c      \
	   ft_isalpha.c      \
	   ft_isascii.c      \
	   ft_isdigit.c      \
	   ft_isprint.c      \
	   ft_memchr.c       \
	   ft_memcmp.c       \
	   ft_memcpy.c       \
	   ft_memmove.c      \
	   ft_memset.c       \
	   ft_strchr.c       \
	   ft_strdup.c       \
	   ft_strlcat.c      \
	   ft_strlcpy.c      \
	   ft_strlen.c       \
	   ft_strncmp.c      \
	   ft_strnstr.c      \
	   ft_strrchr.c      \
	   ft_tolower.c      \
	   ft_toupper.c      \
	   ft_substr.c       \
	   ft_strjoin.c      \
	   ft_strtrim.c      \
	   ft_split.c        \
	   ft_putchar_fd.c   \
	   ft_putstr_fd.c    \
	   ft_putendl_fd.c   \
	   ft_putnbr_fd.c    \
	   ft_striteri.c     \
	   ft_strmapi.c      \
	   ft_itoa.c         \
	   get_next_line.c   \
	   ft_lstnew.c       \
	   ft_lstadd_front.c \
	   ft_lstsize.c      \
	   ft_lstlast.c      \
	   ft_lstadd_back.c  \
	   ft_lstdelone.c    \
	   ft_lstclear.c     \
	   ft_lstiter.c      \
	   ft_lstmap.c       \
	   ft_lstfree.c      \
	   ft_free_tab.c     \
	   ft_printf/srcs/ft_printf.c            \
	   ft_printf/srcs/ft_putchar_count.c     \
	   ft_printf/srcs/ft_putnbr_base_count.c \
	   ft_printf/srcs/ft_putnbr_count.c      \
	   ft_printf/srcs/ft_putptr_count.c      \
	   ft_printf/srcs/ft_putstr_count.c

OBJS = ${SRCS:.c=.o}

# This is a minimal set of ANSI/VT100 color codes
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_UP=\033[1A
_CLEAR=\033[K

# Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY=\x1b[40m
_IRED=\x1b[41m
_IGREEN=\x1b[42m
_IYELLOW=\x1b[43m
_IBLUE=\x1b[44m
_IPURPLE=\x1b[45m
_ICYAN=\x1b[46m
_IWHITE=\x1b[47m

all: ${NAME}

${NAME}: ft_printf ${OBJS}
	@echo -e "${_UP}${_CLEAR}[${_CYAN}Compiling${_END} ${_BOLD}libft... ${_GREEN}Done!${_END}]"
	@echo -e "[${_PURPLE}Linking${_END} ${_BOLD}libft...${_END}]"
	@ar rcs ${NAME} ${OBJS} ft_printf/libftprintf.a
	@echo -e "${_UP}${_CLEAR}[${_PURPLE}Linking${_END} ${_BOLD}libft... ${_GREEN}Done!${_END}]"

ft_printf:
	@make -s -C ft_printf
	@echo -e "tmp"

.c.o:
	@echo -e "${_UP}${_CLEAR}[${_CYAN}Compiling${_END} ${_BOLD}libft... ${_YELLOW}$<${_END}]"
	@${CC} ${CFLAGS} -I ft_printf/include/ -c $< -o $@

clean:
	@make -s -C ft_printf fclean
	@rm -f ${OBJS}
	@echo -e "[${_RED}CLeaning${_END} ${_BOLD}libft... ${_GREEN}Done!${_END}]"

fclean: clean
	@rm -f ${NAME}
	@echo -e "${_UP}${_CLEAR}[${_RED}Fully cleaning${_END} ${_BOLD}libft... ${_GREEN}Done!${_END}]"

re: fclean all

.PHONY: all clean ft_printf fclean re
