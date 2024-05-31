/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:08:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:03:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_shlvl(char **envp)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", ft_strlen("SHLVL")))
		{
			j = 0;
			while (envp[i][j] != '=')
				j++;
			j += 1;
			if (ft_atoi(envp[i] + j))
			{
				new = ft_itoa(ft_atoi(envp[i] + j) + 1);
				free(envp[i]);
				envp[i] = 0;
				envp[i] = strjoin(ft_strdup("SHLVL="), new);
				free(new);
			}
		}
	}
}

static char	**copy_env_null(void)
{
	char	**new_env;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	new_env = ft_calloc(5, sizeof(char *));
	if (!new_env)
		return (0);
	new_env[0] = strjoin(new_env[0], "OLDPWD");
	new_env[1] = strjoin(new_env[1], "SHLVL=");
	new_env[1] = strjoin(new_env[1], "1");
	new_env[2] = strjoin(new_env[2], "_=");
	new_env[3] = strjoin(new_env[3], "PWD=");
	new_env[3] = strjoin(new_env[3], pwd);
	return (new_env);
}

static void	check_in(char ***env)
{
	char	*str;
	char	pwd[PATH_MAX];
	char	*shlvl;

	if (!check_already_in("OLDPWD", *env))
		put_var(env, "OLDPWD", 0);
	if (!check_already_in("SHLVL=", *env))
	{
		shlvl = strjoin(0, "SHLVL=");
		shlvl = strjoin(shlvl, "1");
		put_var(env, shlvl, 0);
		free(shlvl);
	}
	if (!check_already_in("_=", *env))
		put_var(env, "_=", 0);
	if (!check_already_in("PWD=", *env))
	{
		getcwd(pwd, PATH_MAX);
		str = strjoin(0, "PWD=");
		str = strjoin(str, pwd);
		put_var(env, str, 0);
		free(str);
	}
}

char	**copy_env(char **envp)
{
	int		i;
	char	**cpy_env;

	i = 0;
	if (!envp[0])
	{
		cpy_env = copy_env_null();
		return (cpy_env);
	}
	while (envp[i])
		i++;
	cpy_env = ft_calloc(i + 1, sizeof(char *));
	if (!cpy_env)
		return (0);
	i = -1;
	while (envp[++i])
		cpy_env[i] = ft_strdup(envp[i]);
	add_shlvl(cpy_env);
	check_in(&cpy_env);
	return (cpy_env);
}
