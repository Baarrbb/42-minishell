/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:23:33 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	refresh_env_pwd(char ***env, char *pwd, char *oldpwd)
{
	char	**tmp;
	int		i;
	int		get_old;

	tmp = *env;
	i = -1;
	get_old = 0;
	while (tmp[++i])
	{
		if (!ft_strncmp(tmp[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			tmp[i] = update_env(tmp[i], "OLDPWD=", oldpwd);
			get_old = 1;
		}
		if (oldpwd && !ft_strncmp(tmp[i], "PWD=", ft_strlen("PWD=")))
			tmp[i] = update_env(tmp[i], "PWD=", pwd);
	}
	if (!get_old)
		put_old(env, oldpwd);
}

static int	ret_cd(int ret, char ***env, char *oldpwd, char *path)
{
	char	pwd[PATH_MAX];
	char	*err_pwd;

	if (!getcwd(pwd, PATH_MAX))
	{
		error_msg(0, 0, 0, 1);
		err_pwd = get_ourenv("OLDPWD=", *env, 0);
		if (err_pwd)
		{
			chdir(err_pwd);
			refresh_env_pwd(env, err_pwd, oldpwd);
			free(err_pwd);
		}
		return (1);
	}
	if (ret == 0)
		return (refresh_env_pwd(env, pwd, oldpwd), 0);
	else if (ret < 0)
		return (error_msg(path, 0, 0, 2), 1);
	else
		return (1);
}

static int	home_case(char ***env)
{
	char	*get_home;
	int		ret;

	ret = 1;
	get_home = get_ourenv("HOME=", *env, 0);
	if (get_home && get_home[0])
		ret = chdir(ourenv_wo_alloc("HOME", *env));
	else
	{
		ft_putstr_fd(ERROR_CD, 2);
		ft_putstr_fd("HOME not set\n", 2);
	}
	free(get_home);
	return (ret);
}

static int	move_cd(char *path, char ***env, char *oldpwd)
{
	int		ret;

	ret = 1;
	if (!path || !ft_strncmp(path, "--\0", 3) || !ft_strncmp(path, "~\0", 2)
		|| !ft_strncmp(path, "~/\0", 3))
	{
		ret = home_case(env);
	}
	else if (!ft_strncmp(path, "-\0", 2) && ourenv_wo_alloc("OLDPWD", *env))
	{
		ret = chdir(ourenv_wo_alloc("OLDPWD", *env));
		if (!ret)
			if (write_secu(ourenv_wo_alloc("OLDPWD", *env), 1) == -1)
				return (0);
		return (ret_cd(ret, env, oldpwd, ourenv_wo_alloc("OLDPWD", *env)));
	}
	else if (!ft_strncmp(path, "-\0", 2) && !ourenv_wo_alloc("OLDPWD", *env))
		error_msg("OLDPWD not set", 0, 0, 3);
	else if (path[0] == '-' && path[1] == '-' && path[3])
		error_msg("--: invalid option", 0, 0, 3);
	else if (path[0] == '-' && path[1])
		error_msg("-", path[1], ": invalid option", 4);
	else
		ret = chdir(path);
	return (ret_cd(ret, env, oldpwd, path));
}

int	our_cd(t_cmd *cmd, char ***env)
{
	int		nb_args;
	char	*arg;
	char	*oldpwd;
	char	oldpwd_fail[PATH_MAX];
	int		ret;

	nb_args = 0;
	if (cmd->cmd && cmd->cmd[0])
	{
		while (cmd->cmd[nb_args])
			nb_args++;
	}
	if (nb_args > 2)
		return (error_msg("too many arguments", 0, 0, 3), 1);
	arg = cmd->cmd[1];
	oldpwd = get_ourenv("PWD=", *env, 0);
	if (!oldpwd && getcwd(oldpwd_fail, PATH_MAX))
		ret = move_cd(arg, env, oldpwd_fail);
	else
		ret = move_cd(arg, env, oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (ret);
}
