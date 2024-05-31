/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:00:49 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_all_quote_hd(char *arg, int c, char **var)
{
	int		j;

	j = 1;
	while (arg[j] && arg[j] != c)
		j++;
	*var = ft_substr(arg, 0, j + 1);
	return (*var);
}

static void	in_single_quote_hd(char **tmp, char **var, char *arg)
{
	char	*new;

	*var = get_all_quote_hd(arg, '\'', var);
	new = remove_quotes(*var);
	*tmp = strjoin(*tmp, new);
	free(new);
}

static void	in_double_quote_hd(char **tmp, char **var, char *arg)
{
	char	*new;

	*var = get_all_quote_hd(arg, '"', var);
	new = remove_quotes(*var);
	*tmp = strjoin(*tmp, new);
	free(new);
}

static void	no_quote_hd(char **tmp, char **var, char *arg)
{
	*var = get_arg(arg);
	*tmp = strjoin(*tmp, *var);
}

char	*remove_all_quotes_hd(char *line)
{
	int		i;
	char	*tmp;
	char	*in;

	tmp = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			in_single_quote_hd(&tmp, &in, &line[i]);
		else if (line[i] == '"')
			in_double_quote_hd(&tmp, &in, &line[i]);
		else
			no_quote_hd(&tmp, &in, &line[i]);
		i += ft_strlen(in);
		free(in);
	}
	return (tmp);
}
