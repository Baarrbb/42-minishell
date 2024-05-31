/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:14:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# define OPEN_MAX 1024
/*test*/
int		start_execute(t_cmd *pipe, char ***envp);

/*checkcomms*/
int		check_commands(t_cmd *commands, int *sortie);

/*redirections :*/
int		check_redirs(t_cmd cmd, int *sortie, char **envp);
void	redirections_pipe_out(t_cmd *command, t_exec *data, int fd);
int		redirections_in(t_cmd *cmd);
void	redirections_pipe_in(t_exec *data, int fd);
int		redirections_out(t_cmd *cmd);

/*pipes opening and closing*/
void	close_all_pipes(int numPipes, int *pipefds);
int		numbers_pipe(t_cmd *list);
int		creation_pipes(t_exec *data);
int		part_two(t_exec *data);

/*signals handling*/
void	sig_ignore(void);
void	sig_default(void);
void	handle_sigint(int sig);
void	signal_starting(void);

/*builtinpipe*/
void	builtinpipe(t_cmd *cmd, char ***env, t_exec *data, t_cmd *start);

/*redirections_open.c*/
void	open_file_out(t_redir *redir, int *fd);
void	open_file_in(t_redir *cmd, int *fd);
int		open_tests(t_redir *ptr, int *fd, int *sortie);

/*redirection_utils.c*/
void	ambiguous_redir(t_redir *ptr, int *fd, int *sortie);
void	expand_remove_quotes(t_cmd cmd, char *exit, char **envp, t_redir *ptr);
int		count_space(t_redir *ptr, int *fd, int *sortie);

/*execute_command.c*/
void	exec_cmd(t_cmd *cmd, t_exec *data, char **envp, t_cmd *start);

/*heredocyipi*/
int		heredoc(t_redir *redir, t_liberate to_free);

/*heredocutils*/
char	*remove_all_quotes_hd(char *line);

/*errorutils*/
void	full_path_error(t_cmd *command);
void	heredoc_sig_handler(int sig);
int		status_update(t_exec *data, int *wait_result, int *status);
char	*remove_dollars(char *file);
char	*remove_doll(char *filename, int i);

/*error*/
void	error_managing(t_cmd *command, char **envp, t_cmd *start);

#endif