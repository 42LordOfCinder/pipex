SHELL = bash

NAME = pipex

NAME_BONUS = pipex_bonus

INCLUDE = ./includes

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c \
	   srcs/utils.c \
	   srcs/parsing.c

SRCS_BONUS = srcs_bonus/main_bonus.c  \
			 srcs_bonus/utils_bonus.c  \
			 srcs_bonus/parsing_bonus.c \
			 srcs_bonus/here_doc_bonus.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

LIBFT_DIR = ./libft

LIBFT = ${LIBFT_DIR}/libft.a

LIBFT_INCLUDE = ${LIBFT_DIR}/include

# This is a minimal set of ANSI/VT100 color codes
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_UP=\x1b[a
_CLEAR=\x1b[2K\r

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

${NAME}: ${LIBFT} ${OBJS}
	@printf "${_CLEAR} ${_YELLOW}${_BOLD}[${_END} Compiling       ${_BOLD}pipex${_END}        ${_GREEN}Done!${_END}${_YELLOW}${_BOLD} ]${_END}"
	@printf "\n ${_PURPLE}${_BOLD}[${_END} Linking         ${_BOLD}pipex${_END}...${_PURPLE}${_BOLD} ]${_END} "
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} -I${INCLUDE} -I${LIBFT_INCLUDE} -o ${NAME}
	@printf "${_CLEAR} ${_PURPLE}${_BOLD}[${_END} Linking         ${_BOLD}pipex${_END}        ${_GREEN}Done!${_END}${_PURPLE}${_BOLD} ]${_END}\n"

bonus: ${NAME_BONUS}

${NAME_BONUS}: ${LIBFT} ${OBJS_BONUS}
	@printf "${_CLEAR} ${_YELLOW}${_BOLD}[${_END} Compiling       ${_BOLD}pipex${_END}        ${_GREEN}Done!${_END}${_YELLOW}${_BOLD} ]${_END}"
	@printf "\n ${_PURPLE}${_BOLD}[${_END} Linking         ${_BOLD}pipex${_END}...${_PURPLE}${_BOLD} ]${_END} "
	@${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -I${INCLUDE} -I${LIBFT_INCLUDE} -o ${NAME_BONUS}
	@printf "${_CLEAR} ${_PURPLE}${_BOLD}[${_END} Linking         ${_BOLD}pipex${_END}        ${_GREEN}Done!${_END}${_PURPLE}${_BOLD} ]${_END}\n"


${LIBFT}:
	@make -s -C libft

%.o: %.c
	@printf "${_CLEAR} ${_YELLOW}${_BOLD}[${_END} Compiling       ${_BOLD}pipex${_END}... ${_CYAN}$<${_END}${_YELLOW}${_BOLD} ]${_END}"
	@${CC} ${CFLAGS} -I${INCLUDE} -I${LIBFT_INCLUDE} -c $< -o $@

clean:
	@make -s -C ${LIBFT_DIR} clean
	@rm -rf ${OBJS_BONUS}
	@rm -rf ${OBJS}
	@printf "${_CLEAR} ${_RED}${_BOLD}[ ${_END}Cleaning        ${_BOLD}pipex${_END}        ${_GREEN}Done!${_END}${_RED}${_BOLD} ]${_END}\n"

fclean:
	@make -s -C ${LIBFT_DIR} fclean
	@rm -rf ${OBJS}
	@rm -rf ${OBJS_BONUS}
	@rm -rf ${NAME_BONUS}
	@rm -rf ${NAME}
	@printf "${_CLEAR} ${_RED}${_BOLD}[ ${_END}Fully cleaning  ${_BOLD}pipex${_END}        ${_GREEN}Done!${_END}${_RED}${_BOLD} ]${_END}\n"

rebonus: fclean bonus

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re
