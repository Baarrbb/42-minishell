/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:06:38 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:02:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_arg_quote(char **tmp, char *arg, char c)
{
	int		j;
	char	*new;

	j = 1;
	while (arg[j] && arg[j] != c)
		j++;
	if (j - 1 > 0)
	{
		new = ft_substr(arg, 1, j - 1);
		*tmp = strjoin(*tmp, new);
		free(new);
	}
	return (arg + j + 1);
}

static char	*add_arg_wo_quote(char **tmp, char *arg)
{
	int		j;
	char	*new;

	j = 0;
	while (arg[j] && arg[j] != '"' && arg[j] != '\'')
		j++;
	new = ft_substr(arg, 0, j);
	*tmp = strjoin(*tmp, new);
	free(new);
	return (arg + j);
}

char	*remove_quotes(char *arg)
{
	char	*tmp;

	tmp = 0;
	if (!arg)
		return (0);
	while (*arg)
	{
		if (*arg == '\'')
			arg = add_arg_quote(&tmp, arg, '\'');
		else if (*arg == '"')
			arg = add_arg_quote(&tmp, arg, '"');
		else
			arg = add_arg_wo_quote(&tmp, arg);
	}
	if (!tmp)
		tmp = ft_strdup("");
	return (tmp);
}
