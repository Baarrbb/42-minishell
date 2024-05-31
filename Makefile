# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 23:25:19 by marvin            #+#    #+#              #
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
_NEW_YELLOW=\x1b[38;5;228m
_GREEN_BOLD=\033[1;32m
_LIGHT_GREY=\x1b[38;5;242m

MAKEFLAGS += --no-print-directory
OPTIONS_PRINTED = /tmp/options_printed
# OPTIONS_PRINTED = ~/sgoinfre/options_printed

SRC_DIR = src
PARS_DIR = $(SRC_DIR)/parsing
EXEC_DIR = $(SRC_DIR)/execution
BUIL_DIR = $(SRC_DIR)/builtins

SRC_MAIN = \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/sanitize.c \
	$(SRC_DIR)/print.c

SRC_PARS = \
	$(PARS_DIR)/copy_env.c \
	$(PARS_DIR)/manage_env.c \
	$(PARS_DIR)/display_prompt.c \
	$(PARS_DIR)/parsing.c \
	$(PARS_DIR)/parsing_utils.c \
	$(PARS_DIR)/check_syntax.c \
	$(PARS_DIR)/print_error_syntax.c \
	$(PARS_DIR)/fill_struct.c \
	$(PARS_DIR)/fill_cmd.c \
	$(PARS_DIR)/fill_redir.c \
	$(PARS_DIR)/manage_list.c \
	$(PARS_DIR)/handle_quote_env.c \
	$(PARS_DIR)/parsing_quotes_env.c \
	$(PARS_DIR)/remove_quotes.c \
	$(PARS_DIR)/no_quote.c \
	$(PARS_DIR)/interpret_env.c \
	$(PARS_DIR)/interpret_env_utils.c

SRC_BUIL = \
	$(BUIL_DIR)/builtins.c \
	$(BUIL_DIR)/cd.c \
	$(BUIL_DIR)/cd_utils.c \
	$(BUIL_DIR)/echo.c \
	$(BUIL_DIR)/env.c \
	$(BUIL_DIR)/export.c \
	$(BUIL_DIR)/export_print.c \
	$(BUIL_DIR)/export_utils.c \
	$(BUIL_DIR)/unset.c \
	$(BUIL_DIR)/pwd.c \
	$(BUIL_DIR)/exit.c

SRC_EXEC = \
	$(EXEC_DIR)/checks_comms.c \
	$(EXEC_DIR)/errors.c \
	$(EXEC_DIR)/execute.c \
	$(EXEC_DIR)/heredoc.c \
	$(EXEC_DIR)/heredoc_utils.c \
	$(EXEC_DIR)/pipes.c \
	$(EXEC_DIR)/redirections.c \
	$(EXEC_DIR)/signals.c \
	$(EXEC_DIR)/builtinpipe.c \
	$(EXEC_DIR)/redirections_utils.c \
	$(EXEC_DIR)/redirections_open.c \
	$(EXEC_DIR)/execute_command.c \
	$(EXEC_DIR)/errors_utils.c

SRC = \
	$(SRC_MAIN) \
	$(SRC_PARS) \
	$(SRC_BUIL) \
	$(SRC_EXEC)

OBJ_DIR = src/obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = libft/libft.a
INC = -I./headers

all : $(NAME)

print_options : $(OPTIONS_PRINTED)

$(OPTIONS_PRINTED) :
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_ROSE)Compiling options$(_END) :  $(CC) $(CFLAGS)\""
	@ /bin/bash -c "echo"
	@ touch $(OPTIONS_PRINTED)

$(NAME) : $(LIBFT) $(OPTIONS_PRINTED) $(OBJ_DIR) $(OBJ)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_NEW_BLUE)Linking files creating binary $(NAME)$(_END)\""
	@ /bin/bash -c "echo -e \"$(CC) $(CFLAGS) $(notdir $(OBJ) $(LIBFT) -lreadline )\""
	@ $(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_GREEN_BOLD)[DONE]$(_END)\"" 

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ /bin/bash -c "printf \"$(_BLUE)Compiling$(_END) %-21s --> %-21s\n\" $(notdir $<) $(notdir $@)"
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT) :
	@ /bin/bash -c "echo -e \"$(_NEW_YELLOW)Entering directory 'libft'$(_END)\""
	@ make -C libft all
	@ /bin/bash -c "echo -e \"$(_NEW_YELLOW)Leaving directory 'libft'$(_END)\""
	@ /bin/bash -c "echo"

clean :
	@ make -C libft clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning object files$(_END)\""
	@ $(RM) $(OBJ_DIR)
	@ $(RM) $(OPTIONS_PRINTED)
	@ $(RM) $(LIBFT)

fclean : clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning archive $(LIBFT) $(_END)\""
	@ $(RM) $(LIBFT)
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning binary$(_END)\""
	@ $(RM) $(NAME)

re : fclean all

val : all
	valgrind --suppressions=./readline.supp --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes ./minishell
