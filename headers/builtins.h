/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:14:03 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# define ERROR_CD "minishell: cd: "
# define ERROR_EXPORT "minishell: export: "
# ifndef LLONG_MAX
#  define LLONG_MAX 9223372036854775807LL
# endif

/* BUILTINS.C */
void	builtingo(t_cmd *cmd, char ***env, t_exec *data);
char	*ourenv_wo_alloc(char *tofind, char **env);

/* ECHO_C */
int		write_secu(char *test, int i);
int		our_echo(char **cmds_args);

/*  CD_C  */
int		our_cd(t_cmd *cmd, char ***env);

/* CD_UTILS.C */
void	error_msg(char *s1, char s2, char *s3, int type);
char	*update_env(char *line, char *new, char *path);
void	put_old(char ***env, char *oldpwd);

/* PWD_C */
int		our_pwd(char **env);

/* EXPORT_C */
int		check_already_in(char *var, char **env);
void	put_var(char ***env, char *var, int add);
int		our_export(t_cmd *cmd, char ***env);

/* EXPORT_PRINT.C */
void	print_export_alpha(char **env, int size);
void	print_error_msg(char *s1, char *s2);

/* EXPORT_UTILS.C */
char	*get_var_wo_add(char *var);
char	*get_name_var(char *var, int add);
char	*get_value(char *var);
int		cmp_name(char *var1, char *var2);
int		get_size(char **env);

/* UNSET_C */
int		our_unset(char **cmds, char **copy_env);

/* ENV_C */
int		our_env(char **env);

/* EXIT_C */
int		our_exit(t_cmd *everything, char **env, t_exec *data, t_cmd *start);

#endif