# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 17:04:31 by marvin            #+#    #+#              #
#    Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This is a minimal set of ANSI/VT100 color codes
_END=\033[0;0m
_BOLD=\033[0;1m
_UNDER=\033[0;4m
_REV=\033[0;7m

# Colors
_GREY=\033[0;30m
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;35m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

# Inverted, i.e. colored backgrounds
_IGREY=\033[0;40m
_IRED=\033[0;41m
_IGREEN=\033[0;42m
_IYELLOW=\033[0;43m
_IBLUE=\033[0;44m
_IPURPLE=\033[0;45m
_ICYAN=\033[0;46m
_IWHITE=\033[0;47m

# Color test
_ROSE=\x1b[38;5;213m
_NEW_BLUE=\x1b[38;5;80m
_GREEN_BOLD=\033[1;32m
_LIGHT_GREY=\x1b[38;5;242m

MAKEFLAGS += --no-print-directory
# OPTIONS_PRINTED = ~/sgoinfre/options_libft
OPTIONS_PRINTED = /tmp/options_libft

OBJ_DIR = obj

SRCS = \
	ft_split.c \
	ft_memset.c \
	ft_strchr.c \
	ft_substr.c \
	ft_strlen.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strtrim.c \
	ft_isprint.c \
	ft_strdup.c \
	ft_itoa.c \
	ft_atoi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isalpha.c

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
NAME = libft.a
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

print_options : $(OPTIONS_PRINTED)

$(OPTIONS_PRINTED) :
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_ROSE)Compiling options$(_END) :  $(CC) $(CFLAGS)\""
	@ /bin/bash -c "echo"
	@ touch $(OPTIONS_PRINTED)

${NAME} : $(OPTIONS_PRINTED) $(OBJ_DIR) ${OBJS}
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_NEW_BLUE)Creating archive $(NAME)$(_END)\""
	@ /bin/bash -c "echo -e \"ar rc $(notdir $(OBJS))\""
	@ ar rc ${NAME} $(OBJS)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_GREEN_BOLD)[DONE]$(_END)\""
	@ /bin/bash -c "echo"

$(OBJ_DIR):
	@ mkdir -p $@

$(OBJ_DIR)/%.o : %.c
	@ /bin/bash -c "printf \"$(_BLUE)Compiling$(_END) %-14s --> %-14s\n\" $< $(notdir $@)"
	@ ${CC} ${CFLAGS} -c $< -o $@

clean :
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning object files$(_END)\""
	@ ${RM} $(OBJ_DIR)
	@ $(RM) $(OPTIONS_PRINTED)

fclean : clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning archive $(NAME) $(_END)\""
	@ ${RM} ${NAME}

re : fclean all

bonus : ${OBJS}
	ar rc ${NAME} ${OBJS}
