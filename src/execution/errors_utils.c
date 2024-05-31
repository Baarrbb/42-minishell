/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:22:43 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	full_path_error(t_cmd *command)
{
	int		i;
	char	*full_cmd;

	i = -1;
	if (command->path)
	{
		while (command->path[++i])
		{
			full_cmd = strjoin(0, command->path[i]);
			full_cmd = strjoin(full_cmd, "/");
			full_cmd = strjoin(full_cmd, command->cmd[0]);
			if (access(full_cmd, X_OK) == 0)
			{
				if (command->path_cmd)
					free(command->path_cmd);
				command->path_cmd = full_cmd;
				break ;
			}
			free(full_cmd);
			full_cmd = 0;
		}
	}
}

void	heredoc_sig_handler(int sig)
{
	int		fd;

	(void)sig;
	fd = open("/dev/null", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	g_sigint_received = 257;
}

int	status_update(t_exec *data, int *wait_result, int *status)
{
	if (data->builtin
		&& (data->builtin[data->index] == 0 || data->numpipes > 1))
		*wait_result = waitpid(data->pid[data->index], status, 0);
	if (*wait_result == -1)
	{
		perror("waitpid error");
		return (0);
	}
	return (1);
}

char	*remove_doll(char *filename, int i)
{
	int		len;
	char	*newstr;
	int		j;

	j = 0;
	len = ft_strlen(filename);
	newstr = malloc(len * sizeof(char));
	while (j < i)
	{
		newstr[j] = filename[j];
		j++;
	}
	j++;
	while (filename[j])
	{
		newstr[j - 1] = filename[j];
		j++;
	}
	newstr[j - 1] = '\0';
	free(filename);
	return (newstr);
}

char	*remove_dollars(char *file)
{
	int		i;
	int		yipi;
	char	*dup;

	i = 0;
	dup = ft_strdup(file);
	yipi = 0;
	while (dup[i])
	{
		if (dup[i] == '"' && yipi == 0)
			yipi = 1;
		else if (dup[i] == '"' && yipi == 1)
			yipi = 0;
		if (dup[i] == '\'' && yipi == 0)
			yipi = 2;
		else if (dup[i] == '\'' && yipi == 2)
			yipi = 0;
		if (dup[i] == '$' && yipi == 0
			&& (dup[i + 1] && (dup[i + 1] == '\'' || dup[i + 1] == '"'))
			&& (dup[i - 1] && dup[i - 1] != '$'))
			dup = remove_doll(dup, i);
		else
			i++;
	}
	return (dup);
}
