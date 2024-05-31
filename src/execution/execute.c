/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:53:56 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_builtins(t_exec *data, t_cmd *command)
{
	int	i;

	i = 0;
	data->builtin = malloc((data->numpipes) * sizeof(int));
	if (!data->builtin)
		return (1);
	while (command)
	{
		if (command->builtin == 1)
			data->builtin[i] = 1;
		else
			data->builtin[i] = 0;
		command = command->next;
		i++;
	}
	return (0);
}

static t_exec	*fill_struct_exec(t_cmd *command)
{
	t_exec	*data;

	data = malloc(1 * sizeof(t_exec));
	if (data == NULL)
		return (0);
	data->index = 0;
	data->numpipes = numbers_pipe(command);
	data->pid = malloc((data->numpipes + 1) * sizeof(pid_t));
	if (data->pid == NULL)
	{
		free(data);
		return (0);
	}
	data->pid[data->numpipes] = '\0';
	if (fill_builtins(data, command))
	{
		free(data->pid);
		free(data);
		return (0);
	}
	if (part_two(data) == 0)
		return (0);
	return (data);
}

static int	signal_waitpid(int status, int *type)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			if (*type == 1)
				printf("\n");
			if (*type == 1)
				*type = 0;
			return (130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			if (*type == 1)
				printf("Quit\n");
			if (*type == 1)
				*type = 0;
			return (131);
		}
	}
	return (-1);
}

static int	handle_waitpid(t_cmd *pipe, t_exec *data)
{
	int	status;
	int	wait_result;
	int	write_val;
	int	signal_status;

	write_val = 1;
	status = 0;
	wait_result = 0;
	data->index = 0;
	while (data->index < data->numpipes)
	{
		if (status_update(data, &wait_result, &status) == 0)
			break ;
		signal_status = signal_waitpid(status, &write_val);
		data->index++;
	}
	if (data->builtin
		&& data->builtin[data->index - 1] == 1 && data->numpipes <= 1)
		return (pipe->exit_val);
	if (signal_status == 130)
		return (130);
	if (signal_status == 131)
		return (131);
	return (WEXITSTATUS(status));
}

int	start_execute(t_cmd *pipe, char ***envp)
{
	t_exec	*data;
	t_cmd	*command;
	t_cmd	*start;
	int		status;

	command = (t_cmd *)pipe;
	start = command;
	data = fill_struct_exec(command);
	if (data == NULL)
		return (-1);
	while (command)
	{
		sig_ignore();
		if (command->builtin && data->numpipes <= 1)
			builtingo(command, envp, data);
		else
			exec_cmd(command, data, *envp, start);
		command = command->next;
		data->pipeindex += 2;
		data->index++;
	}
	close_all_pipes(data->numpipes, data->pipefds);
	status = handle_waitpid(pipe, data);
	free_struct_exec(data);
	return (status);
}
