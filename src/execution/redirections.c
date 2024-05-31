/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:27:29 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirs(t_cmd cmd, int *sortie, char **envp)
{
	int		fd;
	t_redir	*ptr;
	char	*exit;

	fd = -2;
	ptr = cmd.redir;
	if (ptr)
	{
		while (ptr)
		{
			if (!ptr->e_filen && ptr->in_read == 0)
				return (ambiguous_redir(ptr, &fd, sortie), 0);
			else if (ptr->in_read == 0 && count_space(ptr, &fd, sortie) == 0)
				return (0);
			exit = ft_itoa(*sortie);
			expand_remove_quotes(cmd, exit, envp, ptr);
			free(exit);
			if (open_tests(ptr, &fd, sortie) == 0)
				return (0);
			if (fd > 0)
				close(fd);
			ptr = ptr->next;
		}
	}
	return (1);
}

void	redirections_pipe_out(t_cmd *command, t_exec *data, int fd)
{
	if (command->next)
	{
		if (fd == -1)
		{
			if (dup2(data->pipefds[data->pipeindex + 1], 1) < 0)
			{
				perror("dup2() failed");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int	redirections_in(t_cmd *cmd)
{
	int			fd;
	t_redir		*newredir;

	if (cmd->redir)
	{
		newredir = cmd->redir;
		fd = -1;
		while (newredir != NULL)
		{
			open_file_in(newredir, &fd);
			if (fd > 0)
				dup2(fd, 0);
			newredir = newredir->next;
		}
		return (fd);
	}
	return (-1);
}

void	redirections_pipe_in(t_exec *data, int fd)
{
	if (data->index != 0)
	{
		if (fd == -1)
		{
			if (dup2(data->pipefds[data->pipeindex - 2], 0) < 0)
			{
				perror("dup2() failed");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int	redirections_out(t_cmd *cmd)
{
	t_redir	*oldredir;
	int		fd;

	if (cmd->redir)
	{
		fd = -1;
		oldredir = cmd->redir;
		while (cmd->redir != NULL)
		{
			open_file_out(cmd->redir, &fd);
			if (fd > 0)
				dup2(fd, 1);
			cmd->redir = cmd->redir->next;
		}
		cmd->redir = oldredir;
		return (fd);
	}
	return (-1);
}
