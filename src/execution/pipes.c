/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:30:32 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	part_two(t_exec *data)
{
	data->pipefds = malloc(((data->numpipes * 2)) * sizeof(int));
	if (data->pipefds == NULL)
	{
		free(data->builtin);
		free(data->pid);
		free(data);
		return (0);
	}
	data->pipeindex = 0;
	if (creation_pipes(data) == 1)
	{
		free(data->builtin);
		free(data->pid);
		free(data->pipefds);
		free(data);
		return (0);
	}
	return (1);
}

void	close_all_pipes(int numPipes, int *pipefds)
{
	int	i;

	i = 0;
	while (i < 2 * numPipes && pipefds[i] != 999999)
	{
		close(pipefds[i]);
		i++;
	}
}

int	numbers_pipe(t_cmd *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (0);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	creation_pipes(t_exec *data)
{
	int	i;

	i = 0;
	while (data->numpipes > i)
	{
		if (pipe(data->pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
			data->pipefds[i * 2] = 999999;
			close_all_pipes(data->numpipes, data->pipefds);
			return (1);
		}
		i++;
	}
	return (0);
}
