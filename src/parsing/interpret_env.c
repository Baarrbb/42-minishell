/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:58 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:03:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	move_on_var(char *var, int type)
{
	int	i;

	if (type)
	{
		i = 0;
		while (var[i] && var[i] != '$')
			i++;
	}
	else
	{
		i = 1;
		while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
	}
	return (i);
}

static char	*get_not_env(char *var, int i, char **new)
{
	char	*tmp;

	if (i != 0)
	{
		tmp = ft_substr(var, 0, i);
		*new = strjoin(*new, tmp);
		free(tmp);
		var += i;
	}
	return (var);
}

static char	*get_name_env(char *var, char **name, int i)
{
	if (i == 1 && var[i] == '?')
	{
		*name = ft_strdup("?=");
		var += i + 1;
	}
	else
	{
		*name = ft_substr(var, 1, i - 1);
		*name = strjoin(*name, "=");
		var += i;
	}
	return (var);
}

static void	add_val_env(char **name, char **envp, char *sortie, char **new)
{
	char	*val;

	val = 0;
	if (*name)
	{
		val = get_ourenv(*name, envp, sortie);
		free(*name);
		if (val)
		{
			*new = strjoin(*new, val);
			free(val);
		}
	}
}

char	*interpret_env(char *var, char **envp, char *sortie)
{
	int		i;
	char	*new;
	char	*name;

	i = 0;
	new = 0;
	while (*var)
	{
		name = 0;
		i = move_on_var(var, 1);
		var = get_not_env(var, i, &new);
		if (*var)
		{
			var = check_digit(var, &new);
			i = move_on_var(var, 0);
			if (i == 1 && (!var[i] || var[i] == ' '))
				var = check_after_dollar(var, &new, i);
			else if (i == 1 && !ft_isalnum(var[i]) && var[i] != '?')
				var = check_after_dollar(var, &new, i);
			else
				var = get_name_env(var, &name, i);
			add_val_env(&name, envp, sortie, &new);
		}
	}
	return (new);
}
