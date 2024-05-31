/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:44:01 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_syntax(char **args, char *line)
{
	char	*token;

	token = 0;
	if ((!line || line[0] == 0) && !args[1])
		token = "newline";
	else if (line[0] == '|' || (args[1] && args[1][0] == '|'))
		token = "|";
	else if ((line[0] == '>' && line[1] == '>')
		|| (args[1] && args[1][0] == '>' && args[1][1] == '>'))
		token = ">>";
	else if ((line[0] == '<' && line[1] == '<')
		|| (args[1] && args[1][0] == '<' && args[1][1] == '<'))
		token = "<<";
	else if (line[0] == '>' || (args[1] && args[1][0] == '>'))
		token = ">";
	else if (line[0] == '<' || (args[1] && args[1][0] == '<'))
		token = "<";
	if (token)
	{
		print_error_syntax(token);
		return (0);
	}
	return (1);
}

static int	check_syntax_redir(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '<' && args[i][1] == '>')
		{
			print_error_syntax("newline");
			return (0);
		}
		else if ((args[i][0] == '>' && args[i][1] == '>')
			|| (args[i][0] == '<' && args[i][1] == '<'))
		{
			if (!error_syntax(&args[i], &args[i][2]))
				return (0);
		}
		else if ((args[i][0] == '>' && args[i][1] != '>')
			|| (args[i][0] == '<' && args[i][1] != '<'))
		{
			if (!error_syntax(&args[i], &args[i][1]))
				return (0);
		}
	}
	return (1);
}

static int	check_syntax_pipe(char **args, int size)
{
	int	i;

	i = -1;
	if (*args && args[0])
	{
		if (args[0][0] == '|' && args[0][1] == '|')
			return (print_error_syntax("||"), 0);
		if (args[0][0] == '|')
			return (print_error_syntax("|"), 0);
		while (args[++i])
		{
			if (args[i][0] == '|' && args[i][1] == '|')
				return (print_error_syntax("||"), 0);
		}
		if (size > 0 && args[size - 1]
			&& args[size - 1][0] && args[size - 1][0] == '|')
			return (print_error_syntax("|"), 0);
		return (1);
	}
	return (0);
}

static int	check_esperluette(char **args)
{
	if (*args && args[0])
	{
		if (args[0][0] == '&' && args[0][1] == '&')
			return (print_error_syntax("&&"), 0);
		else if (args[0][0] == '&')
			return (print_error_syntax("&"), 0);
		return (1);
	}
	return (0);
}

int	check_syntax(char **args, int size)
{
	return (check_esperluette(args)
		&& check_syntax_redir(args) && check_syntax_pipe(args, size));
}
