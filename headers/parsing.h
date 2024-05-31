/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:27:19 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define ERROR_MSG "minishell: syntax error near unexpected token "

/* PARSING_C */
int		check_line(char *line, t_cmd **pipe, char **envp, int *sortie);

/* PARSING_UTILS_C */
char	*strjoin(char *dst, char *s);
int		is_space(int c);
int		is_spe_char(int c);
char	**new_cmd(t_cmd *cmd);

/* CHECK_SYNTAX_C */
int		check_syntax(char **args, int size);

/* PRINT_ERROR_SYNTAX.C */
void	print_error_syntax(char *s1);

/* FILL_STRUCT_C */
int		fill_struct(t_cmd **pipe, char **args, char **envp, int *sortie);

/* FILL_CMD_C */
void	fill_cmd(t_cmd **pipe, char **args);

/* FILL_REDIR_C */
int		is_redir(t_cmd **cmd, char **args, int i);

/*  MANAGE_LIST_C  */
void	ft_lstadd_back(t_redir **lst, t_redir *new);
void	ft_lstadd_back_bis(t_cmd **lst, t_cmd *new);

/* HANDLE_QUOTE_ENV.C */
char	*get_ourenv(char *tofind, char **ourenv, char *sortie);
int		handle_quoting(t_cmd *cmd, char **env, int *sortie);

/* PARSING_QUOTES_ENV.C */
char	*get_var_env(t_cmd *cmd, char *arg, char **env, char *sortie);

/* REMOVE_QUOTES.C */
char	*remove_quotes(char *arg);

/* NO_QUOTE.C */
char	*no_quote(t_cmd *cmd, t_env g_env, char *sortie);
char	*no_q_af_nul(t_cmd *cmd, t_env g_env, char *sortie);
char	*get_arg(char *arg);

/* INTERPRET_ENV.C */
char	*interpret_env(char *var, char **envp, char *sortie);

/* INTERPRET_ENV_UTILS.C */
char	*check_digit(char *var, char **new);
char	*check_after_dollar(char *var, char **new, int i);

/* GET_ENV.C */
char	**copy_env(char **envp);

/* MANAGE_ENV.C */
void	changevar(t_cmd *cmd, char **envp);

/* DISPLAY_PROMPT.C */
char	*display_prompt(char **env);

/* SANITIZE_C */
void	free_char_tab(char **tab);
void	free_list(t_cmd **list);
void	free_struct_exec(t_exec *data);

/*  PRINT_C */
int		print_struct(t_cmd *cmd);
void	print_redir(t_redir *redir);
void	print_linked_list(t_cmd *pipe);
void	print_char_tab(char **tab);

#endif