/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:08:30 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir(t_redir *redir)
{
	if (redir)
	{
		while (redir)
		{
			printf("out %d end %d\n", redir->out, redir->out_end);
			printf("in %d read %d\n", redir->in, redir->in_read);
			printf("Filename .%s.\n", redir->filename);
			printf("Filename expand .%s.\n", redir->e_filen);
			redir = redir->next;
		}
	}
}

int	print_struct(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (printf("NULL\n"), 0);
	if (!cmd->cmd || !cmd->cmd[0])
		printf("\ncmd->cmd : 2(null)\n");
	else if ((!cmd->cmd || !cmd->cmd[0]) && cmd->redir)
		print_redir(cmd->redir);
	else if (cmd->cmd && cmd->cmd[0])
	{
		i = -1;
		while (cmd->cmd[++i])
		{
			if (i == 0)
				printf("\ncmd : 1.%s.\n", cmd->cmd[i]);
			else
				printf("args : .%s.\n", cmd->cmd[i]);
		}
	}
	printf("Is that a builtin : %d\n", cmd->builtin);
	printf("Cmd path : %s\n", cmd->path_cmd);
	if (cmd->redir)
		print_redir(cmd->redir);
	return (0);
}

void	print_linked_list(t_cmd *pipe)
{
	while (pipe)
	{
		print_struct(pipe);
		pipe = pipe->next;
	}
}

void	print_char_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			printf(".%s.\n", tab[i]);
	}
}
