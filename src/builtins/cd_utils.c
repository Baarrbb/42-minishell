/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:38:44 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:00:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *s1, char s2, char *s3, int type)
{
	ft_putstr_fd(ERROR_CD, 2);
	if (type == 1)
		ft_putstr_fd("error retrieving current directory: getcwd: cannot "
			"access parent directories: ", 2);
	else if (type == 2)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
	}
	else if (type == 3)
		ft_putstr_fd(s1, 2);
	else if (type == 4)
	{
		ft_putstr_fd(s1, 2);
		ft_putchar_fd(s2, 2);
		ft_putstr_fd(s3, 2);
	}
	if (type == 1 || type == 2)
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

char	*update_env(char *line, char *new, char *path)
{
	free(line);
	line = 0;
	line = strjoin(line, new);
	if (path)
		line = strjoin(line, path);
	return (line);
}

void	put_old(char ***env, char *oldpwd)
{
	char	*line;

	line = strjoin(0, "OLDPWD=");
	if (oldpwd)
		line = strjoin(line, oldpwd);
	put_var(env, line, 0);
	free(line);
}
