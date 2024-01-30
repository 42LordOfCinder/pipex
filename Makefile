SHELL = bash

NAME = pipex

INCLUDES = includes

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c \
	   srcs/parsing_utils.c

OBJS = ${SRCS:.c=.o}

# This is a minimal set of ANSI/VT100 color codes
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m

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

${NAME}: ${OBJS}
	@make -s -C libft
	@echo -e "${_CYAN}Linking${_END} ${_BOLD}${NAME}${_END}${_CYAN}...${_END}"
	@${CC} ${CFLAGS} $^ -o $@ -L. libft/libft.a
	@echo -e "${_BOLD}${_GREEN}Done!${_END}"

%.o: %.c
	@echo -e "${_YELLOW}Compiling${_END} ${_BOLD}$<${_END}"
	@${CC} ${CFLAGS} -I ./${INCLUDES} -c $< -o $@

clean:
	@make -s fclean -C libft
	@echo -e "${_YELLOW}Cleaning${_END} ${_BOLD}${OBJS}${_END}"
	@rm -rf ${OBJS}
	@echo -e "${_BOLD}${_GREEN}Done!${_END}"

fclean: clean
	@echo -e "${_YELLOW}Cleaning${_END} ${_BOLD}${NAME}${_END}"
	@rm -rf ${NAME}
	@echo -e "${_BOLD}${_GREEN}Done!${_END}"

re: fclean all

.PHONY: all clean fclean re
