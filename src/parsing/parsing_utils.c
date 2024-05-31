/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:27:26 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dst_null(char	*dst)
{
	dst = (char *)malloc(1 * sizeof(char));
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	return (dst);
}

char	*strjoin(char *dst, char *s)
{
	char	*res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!dst)
		dst = dst_null(dst);
	res = (char *)malloc((ft_strlen(s) + ft_strlen(dst) + 1) * sizeof(char));
	if (!res)
		return (free(dst), NULL);
	i = -1;
	j = -1;
	if (dst)
	{
		while (dst[++i])
			res[i] = dst[i];
	}
	while (s[++j])
		res[i++] = s[j];
	res[i] = '\0';
	free(dst);
	return (res);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_spe_char(int c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	**new_cmd(t_cmd *cmd)
{
	char	*new_cmd;
	char	**new_split;
	int		i;

	new_split = 0;
	new_cmd = 0;
	i = -1;
	if (!cmd->cmd[0] || !cmd->cmd[0][0])
		return (cmd->cmd);
	while (cmd->cmd[++i])
	{
		new_cmd = strjoin(new_cmd, cmd->cmd[i]);
		new_cmd = strjoin(new_cmd, " ");
	}
	new_split = ft_split(new_cmd, ' ');
	free(new_cmd);
	free_char_tab(cmd->cmd);
	return (new_split);
}
