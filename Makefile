SHELL = bash

NAME = pipex

NAME_BONUS = pipex

INCLUDES = includes

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c \
	   srcs/utils.c

SRCS_BONUS = srcs_bonus/main_bonus.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

LIB = libft/libft.a

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

${NAME}: ${LIB} ${OBJS}
	@echo -e "${_UP}${_CLEAR}[${_CYAN}Compiling${_END} ${_BOLD}pipex... ${_GREEN}Done!${_END}]"
	@echo -e "[${_PURPLE}Linking${_END} ${_BOLD}pipex...${_END}]"
	@${CC} ${CFLAGS} $^ -o $@ -L. ${LIB}
	@echo -e "${_UP}${_CLEAR}[${_PURPLE}Linking${_END} ${_BOLD}pipex... ${_GREEN}Done!${_END}]"

bonus: ${LIB} ${OBJS_BONUS}
	@echo -e "${_UP}${_CLEAR}[${_CYAN}Compiling${_END} ${_BOLD}pipex... ${_GREEN}Done!${_END}]"
	@echo -e "[${_PURPLE}Linking${_END} ${_BOLD}pipex...${_END}]"
	@${CC} ${CFLAGS} $^ -o ${NAME_BONUS} -L. ${LIB}
	@echo -e "${_UP}${_CLEAR}[${_PURPLE}Linking${_END} ${_BOLD}pipex... ${_GREEN}Done!${_END}]"

${LIB}:
	@make -s -C libft
	@echo -e "tmp"

%.o: %.c
	@echo -e "${_UP}${_CLEAR}[${_CYAN}Compiling${_END} ${_BOLD}pipex... ${_YELLOW}$<${_END}]"
	@${CC} ${CFLAGS} -I ./${INCLUDES} -c $< -o $@

clean:
	@make -s -C libft fclean
	@rm -rf ${OBJS_BONUS}
	@rm -rf ${OBJS}
	@echo -e "[${_RED}Cleaning${_END} ${_BOLD}pipex... ${_GREEN}Done${_END}]"

fclean: clean
	@rm -rf ${NAME}
	@echo -e "${_UP}${_CLEAR}[${_RED}Fully cleaning${_END} ${_BOLD}pipex... ${_GREEN}Done${_END}]"

re: fclean all

.PHONY: all clean fclean re
