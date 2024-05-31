/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:40:50 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	testing_redirs(t_cmd *cmd, t_exec *data, char ***envp, t_cmd *start)
{
	int	i;

	i = 0;
	sig_default();
	if (check_redirs(*cmd, &i, *envp) == 0)
	{
		close_all_pipes(data->numpipes, data->pipefds);
		free_struct_exec(data);
		free_list(&start);
		free_char_tab(*envp);
		exit(i);
	}
}

static void	exec_cmd_utils(t_cmd *cmd, t_exec *data, char ***envp, t_cmd *start)
{
	int	i;

	i = 0;
	sig_default();
	testing_redirs(cmd, data, envp, start);
	cmd->fdinopen = redirections_in(cmd);
	redirections_pipe_in(data, cmd->fdinopen);
	cmd->fdoutopen = redirections_out(cmd);
	redirections_pipe_out(cmd, data, cmd->fdoutopen);
	if (cmd->fdinopen > 0)
		close(cmd->fdinopen);
	if (cmd->fdoutopen > 0)
		close(cmd->fdoutopen);
	if (cmd->builtin == 1)
	{
		builtinpipe(cmd, envp, data, start);
		i = cmd->exit_val;
		close_all_pipes(data->numpipes, data->pipefds);
		free_struct_exec(data);
		free_list(&start);
		free_char_tab(*envp);
		exit(i);
	}
	close_all_pipes(data->numpipes, data->pipefds);
	free_struct_exec(data);
}

void	exec_cmd(t_cmd *cmd, t_exec *data, char **envp, t_cmd *start)
{
	data->pid[data->index] = fork();
	if (data->pid[data->index] == 0)
	{
		exec_cmd_utils(cmd, data, &envp, start);
		error_managing(cmd, envp, start);
		if (execve(cmd->path_cmd, cmd->cmd, envp) < 0)
		{
			perror(cmd->path_cmd);
			free_list(&cmd);
			free_char_tab(envp);
			exit(126);
		}
	}
	else if (data->pid[data->index] < 0)
	{
		perror("fork() failed");
		free_list(&cmd);
		free_char_tab(envp);
		exit(EXIT_FAILURE);
	}
}
