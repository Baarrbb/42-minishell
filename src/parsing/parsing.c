/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:36:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quote(char *line)
{
	while (*line != '\'' && *line != '\"' && *line)
		line++;
	while (*line)
	{
		if (*line == '\'')
		{
			line++;
			while (*line != '\'' && *line)
				line++;
			if (*line == 0)
				return (0);
		}
		else if (*line == '\"')
		{
			line++;
			while (*line != '\"' && *line)
				line++;
			if (*line == 0)
				return (0);
		}
		line++;
		while (*line != '\'' && *line != '\"' && *line)
			line++;
	}
	return (1);
}

static int	get_next_quote(char *line, int i)
{
	if (line[i] == '\'' && line[i])
	{
		i++;
		while (line[i] != '\'')
			i++;
	}
	if (line[i] == '\"' && line[i])
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
	}
	i++;
	return (i);
}

static int	get_nb_args(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (is_space(line[i]) && line[i])
			i++;
		while (!is_space(line[i]) && !is_spe_char(line[i]) && line[i])
			i = get_next_quote(line, i);
		if (i - 1 >= 0 && !is_space(line[i - 1]) && !is_spe_char(line[i - 1]))
			count++;
		if (is_spe_char(line[i]))
		{
			while (is_spe_char(line[i]) && line[i])
				i++;
			count++;
		}
		while (is_space(line[i]) && line[i])
			i++;
	}
	return (count);
}

static char	**fill_args(char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*line)
	{
		while (is_space(*line) && *line)
			line++;
		i = 0;
		while (!is_space(line[i]) && !is_spe_char(line[i]) && line[i])
			i = get_next_quote(line, i);
		if (i)
			args[j++] = ft_substr(line, 0, i);
		line += i;
		while (is_space(*line) && *line)
			line++;
		i = 0;
		while (is_spe_char(line[i]))
			i++;
		if (i)
			args[j++] = ft_substr(line, 0, i);
		line += i;
	}
	return (args);
}

int	check_line(char *line, t_cmd **pipe, char **envp, int *sortie)
{
	char	**args;
	int		size;

	if (!check_quote(line))
	{
		printf("minishell: syntax error quote expected\n");
		return (free(line), 1);
	}
	size = get_nb_args(line);
	if (!size)
		return (free(line), 1);
	args = ft_calloc(size + 1, sizeof(char *));
	if (!args)
		return (printf("Error on allocation\n"), free(line), 0);
	fill_args(args, line);
	if (!check_syntax(args, size))
	{
		*sortie = 2;
		return (free_char_tab(args), free(line), 1);
	}
	if (!fill_struct(pipe, args, envp, sortie))
		return (free_char_tab(args), free(line),
			printf("Error on allocation\n"), 0);
	free(line);
	return (1);
}
