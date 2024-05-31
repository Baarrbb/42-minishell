/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:17:08 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:02:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg(char *arg)
{
	int		i;
	char	*var;

	i = 0;
	while (arg[i] && arg[i] != '"' && arg[i] != '\'')
		i++;
	var = ft_substr(arg, 0, i);
	return (var);
}

static void	epur_str(char *str)
{
	char	*dest;

	dest = str;
	while (*str != '\0')
	{
		while (*str == ' ' && *(str + 1) == ' ')
			str++;
		*dest++ = *str++;
	}
	*dest = '\0';
}

char	*no_quote(t_cmd *cmd, t_env g_env, char *sortie)
{
	char	*val;
	char	*new;
	char	*var;

	var = get_arg(g_env.arg);
	if (ft_strchr(var, '$'))
	{
		cmd->is_env = 1;
		val = interpret_env(var, g_env.env, sortie);
		new = ft_strtrim(val, " ");
		free(val);
		if (new)
		{
			epur_str(new);
			*g_env.tmp = strjoin(*g_env.tmp, new);
			free(new);
		}
	}
	else
		*g_env.tmp = strjoin(*g_env.tmp, var);
	return (var);
}

char	*no_q_af_nul(t_cmd *cmd, t_env g_env, char *sortie)
{
	char	*val;
	char	*new;
	char	*var;

	var = get_arg(g_env.arg + 2);
	if (ft_strchr(var, '$'))
	{
		cmd->is_env = 1;
		val = interpret_env(var, g_env.env, sortie);
		new = ft_strtrim(val, " ");
		if (val)
			*g_env.tmp = strjoin(*g_env.tmp, " ");
		free(val);
		if (new)
		{
			epur_str(new);
			*g_env.tmp = strjoin(*g_env.tmp, new);
			free(new);
		}
	}
	else
		*g_env.tmp = strjoin(*g_env.tmp, var);
	return (var);
}
