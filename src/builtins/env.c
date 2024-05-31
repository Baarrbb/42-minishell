/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:46:44 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_env(char **env)
{
	int	i;

	i = -1;
	if (env)
	{
		while (env[++i])
		{
			if (ft_strchr(env[i], '='))
			{
				if (write(1, env[i], ft_strlen(env[i])) == -1)
				{
					perror("write error");
					return (0);
				}
				if (write(1, "\n", 1) == -1)
				{
					perror("write error");
					return (0);
				}
			}
		}
	}
	return (0);
}
