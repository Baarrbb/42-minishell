/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_comms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:15:32 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_notfound(t_cmd *cmd, int *sortie)
{
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	*sortie = 127;
}

static void	error_filename(t_cmd *cmd, int *sortie)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": filename argument required\n", 2);
	*sortie = 2;
}

static void	replace_commands(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->cmd[0][i])
		i++;
	i--;
	while (cmd->cmd[0][i] != '/')
		i--;
	tmp = cmd->path_cmd;
	cmd->path_cmd = cmd->cmd[0];
	cmd->cmd[0] = ft_strdup(&cmd->cmd[0][i + 1]);
	free(tmp);
}

static void	check_replace_cmd(t_cmd *commands)
{
	if (commands->cmd[0][0] && commands->cmd[0][0] == '/')
		replace_commands(commands);
}

int	check_commands(t_cmd *commands, int *sortie)
{
	while (commands)
	{
		if (commands->cmd && commands->cmd[0])
		{
			if (commands->cmd[0][0] == '\0')
				return (error_notfound(commands, sortie), 127);
			if (commands->cmd[0][0] && commands->cmd[0][0] == '.')
			{
				if (commands->cmd[0][1] == '\0')
					return (error_filename(commands, sortie), 2);
				if (commands->cmd[0][1] && commands->cmd[0][1] == '.')
				{
					if (commands->cmd[0][2] == '\0')
						return (error_notfound(commands, sortie), 127);
					if (commands->cmd[0][2] && commands->cmd[0][2] == '/')
						replace_commands(commands);
				}
				else if (commands->cmd[0][1] && commands->cmd[0][1] == '/')
					replace_commands(commands);
			}
			check_replace_cmd(commands);
		}
		commands = commands->next;
	}
	return (0);
}
