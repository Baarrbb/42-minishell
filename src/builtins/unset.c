/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_elem(char ***arr, int index)
{
	int	i;

	i = index;
	free((*arr)[i]);
	while ((*arr)[i] != NULL)
	{
		(*arr)[i] = (*arr)[i + 1];
		i++;
	}
	(*arr)[i] = NULL;
}

int	our_unset(char **cmds, char **copy_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (copy_env[i])
	{
		j = 1;
		while (cmds[j])
		{
			if (ft_strncmp(copy_env[i], cmds[j], ft_strlen(cmds[j])) == 0)
				if (copy_env[i][ft_strlen(cmds[j])] == '=')
					remove_elem(&copy_env, i);
			j++;
		}
		i++;
	}
	i = 0;
	return (0);
}
