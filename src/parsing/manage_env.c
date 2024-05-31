/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:08:59 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	to_var(char **envp, char *str)
{
	char	*newstr;
	int		l;

	newstr = 0;
	l = 0;
	while (envp[l] && (envp[l][0] != '_' && envp[l][1] != '='))
		l++;
	if (envp[l])
	{
		if (str)
			newstr = strjoin(ft_strdup("_="), str);
		else
			newstr = strjoin(ft_strdup("_="), "");
		free(envp[l]);
		envp[l] = newstr;
	}
}

void	changevar(t_cmd *cmd, char **envp)
{
	int		i;

	i = 0;
	if (cmd->next == NULL)
	{
		if (cmd->cmd && cmd->cmd[0])
		{
			while (cmd->cmd[i + 1])
				i++;
			to_var(envp, cmd->cmd[i]);
		}
		else
			to_var(envp, 0);
	}
}
