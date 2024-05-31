/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:23 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_secu(char *test, int i)
{
	if (write(1, test, ft_strlen(test)) == -1)
	{
		perror("write error");
		return (0);
	}
	if (i == 1)
	{
		if (write(1, "\n", 1) == -1)
		{
			perror("write error");
			return (0);
		}
	}
	return (1);
}

static int	good_flag(char *arguments)
{
	int	i;

	i = 1;
	if (!arguments)
		return (1);
	if (arguments[0] != '-')
		return (1);
	while (arguments[i])
	{
		if (arguments[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	our_echo(char **cmds_args)
{
	int	next_line;
	int	i;

	i = 0;
	next_line = 1;
	if (cmds_args[1] == NULL)
	{
		write_secu("\n", 0);
		return (0);
	}
	while (good_flag(cmds_args[++i]) == 0)
		next_line = 0;
	while (cmds_args[i])
	{
		if (write_secu(cmds_args[i], 0) == 0)
			return (0);
		if (cmds_args[i + 1] != NULL)
			if (write_secu(" ", 0) == 0)
				return (0);
		i++;
	}
	if (next_line == 1)
		if (write_secu("\n", 0) == 0)
			return (0);
	return (0);
}
