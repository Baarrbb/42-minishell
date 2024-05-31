/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:21:22 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:03:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_digit(char *var, char **new)
{
	int		i;
	char	*tmp;

	if (var[0] == '$' && ft_isdigit(var[1]))
	{
		i = 2;
		while (var[i] && var[i] != '$')
			i++;
		tmp = ft_substr(var, 2, i - 2);
		*new = strjoin(*new, tmp);
		free(tmp);
		if (var[i])
			var += i - 2;
	}
	return (var);
}

char	*check_after_dollar(char *var, char **new, int i)
{
	char	*tmp;

	if (!var[i] || var[i] == ' ')
	{
		*new = strjoin(*new, "$");
		var += i;
	}
	else if (!ft_isalnum(var[i]) && var[i] != '?')
	{
		while (var[i] && !ft_isalnum(var[i]))
			i++;
		tmp = ft_substr(var, 0, i);
		*new = strjoin(*new, tmp);
		free(tmp);
		var += i;
	}
	return (var);
}
