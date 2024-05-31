/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:11:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:02:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_all_quote(t_cmd *cmd, char *arg, int c, char **var)
{
	int		j;

	j = 1;
	if (c == '"')
		cmd->cmd_quote = 1;
	while (arg[j] && arg[j] != c)
		j++;
	*var = ft_substr(arg, 0, j + 1);
	return (*var);
}

static void	in_single_quote(t_cmd *cmd, char **tmp, char **var, char *arg)
{
	char	*new;

	*var = get_all_quote(cmd, arg, '\'', var);
	cmd->cmd_quote = 1;
	new = remove_quotes(*var);
	if (!new[0])
		cmd->quote_null = 1;
	*tmp = strjoin(*tmp, new);
	free(new);
}

static void	in_double_quote(t_cmd *cmd, t_env g_env, char *sortie)
{
	char	*val;
	char	*new;

	new = remove_quotes(g_env.arg);
	if (ft_strchr(new, '$'))
	{
		cmd->is_env = 1;
		cmd->env_quote = 1;
		val = interpret_env(new, g_env.env, sortie);
		if (val)
		{
			*g_env.tmp = strjoin(*g_env.tmp, val);
			free(val);
			val = 0;
		}
		else
			*g_env.tmp = strjoin(*g_env.tmp, "");
	}
	else if (new)
		*g_env.tmp = strjoin(*g_env.tmp, new);
	if (!new[0])
		cmd->quote_null = 1;
	free(new);
}

static void	remove_dollar_quotes_empty(char *str)
{
	char	*src;
	char	*dst;

	if (!str)
		return ;
	src = str;
	dst = str;
	while (*src)
	{
		if (*src == '$')
		{
			if (*(src + 1) == '"' && *(src + 2) == '"')
				src += 3;
			else if (*(src + 1) == '\'' && *(src + 2) == '\'')
				src += 3;
			else if (*(src + 1) == '"' || *(src + 1) == '\'')
				src += 1;
			else
				*dst++ = *src++;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_var_env(t_cmd *cmd, char *arg, char **env, char *sortie)
{
	char	*var;
	char	*tmp;
	int		j;

	j = 0;
	tmp = 0;
	while (arg[j])
	{
		if (arg[j] == '\'')
			in_single_quote(cmd, &tmp, &var, &arg[j]);
		else if (arg[j] == '"')
			in_double_quote(cmd, (t_env){env, &tmp,
				get_all_quote(cmd, &arg[j], '"', &var)}, sortie);
		else
		{
			remove_dollar_quotes_empty(&arg[j]);
			if (j > 2 && arg[j - 1] == '"' && arg[j - 2] == '"')
				var = no_q_af_nul(cmd, (t_env){env, &tmp, &arg[j - 2]}, sortie);
			else
				var = no_quote(cmd, (t_env){env, &tmp, &arg[j]}, sortie);
		}
		j += ft_strlen(var);
		free(var);
	}
	return (tmp);
}
