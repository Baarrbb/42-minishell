/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:42:57 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:03:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_home(char *pwd, char **env)
{
	char	*home;
	char	*parse_pwd;

	parse_pwd = 0;
	home = 0;
	home = get_ourenv("HOME=", env, 0);
	if (!home)
		return (ft_strdup(pwd));
	if (!ft_strncmp(pwd, home, ft_strlen(home)))
	{
		parse_pwd = strjoin(parse_pwd, "~");
		pwd += ft_strlen(home);
		free(home);
		if (!pwd)
			return (parse_pwd);
		parse_pwd = strjoin(parse_pwd, pwd);
		return (parse_pwd);
	}
	else
		return (free(home), ft_strdup(pwd));
}

char	*display_prompt(char **env)
{
	char	*parse_pwd;
	char	*prompt;
	char	*pwd;
	char	our_pwd[PATH_MAX];

	prompt = 0;
	pwd = ourenv_wo_alloc("PWD", env);
	if (pwd)
		parse_pwd = parse_home(pwd, env);
	else if (getcwd(our_pwd, PATH_MAX))
		parse_pwd = parse_home(our_pwd, env);
	else
		parse_pwd = 0;
	prompt = strjoin(prompt, "minishell: ");
	prompt = strjoin(prompt, "\001" CYAN "\002");
	if (parse_pwd)
		prompt = strjoin(prompt, parse_pwd);
	if (parse_pwd)
		free(parse_pwd);
	prompt = strjoin(prompt, "\001" RESET "\002");
	prompt = strjoin(prompt, " $ ");
	return (prompt);
}
