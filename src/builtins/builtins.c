/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:37:27 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ourenv_wo_alloc(char *tofind, char **env)
{
	int	i;

	if (env)
	{
		i = -1;
		while (env[++i])
		{
			if (ft_strchr(env[i], '='))
			{
				if (!ft_strncmp(env[i], tofind, ft_strlen(tofind)))
					return (env[i] + ft_strlen(tofind) + 1);
			}
		}
	}
	return (0);
}

static void	command_exec(t_cmd *cmd, char ***env, t_exec *data)
{
	if (!cmd->cmd[0])
		return ;
	if (!ft_strncmp(cmd->cmd[0], "echo", ft_strlen("echo")))
		cmd->exit_val = our_echo(cmd->cmd);
	else if (!ft_strncmp(cmd->cmd[0], "cd", ft_strlen("cd")))
		cmd->exit_val = our_cd(cmd, env);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", ft_strlen("pwd")))
		cmd->exit_val = our_pwd(*env);
	else if (!ft_strncmp(cmd->cmd[0], "export", ft_strlen("export")))
		cmd->exit_val = our_export(cmd, env);
	else if (!ft_strncmp(cmd->cmd[0], "unset", ft_strlen("unset")))
		cmd->exit_val = our_unset(cmd->cmd, *env);
	else if (!ft_strncmp(cmd->cmd[0], "env", ft_strlen("env")))
		cmd->exit_val = our_env(*env);
	else if (!ft_strncmp(cmd->cmd[0], "exit", ft_strlen("exit")))
	{
		close(data->fdsave[0]);
		close(data->fdsave[1]);
		cmd->exit_val = our_exit(cmd, *env, data, 0);
	}
}

void	builtingo(t_cmd *cmd, char ***env, t_exec *data)
{
	int	i;

	i = 0;
	if (check_redirs(*cmd, &i, *env) == 0)
	{
		cmd->exit_val = i;
		return ;
	}
	data->fdsave[0] = dup(0);
	data->fdsave[1] = dup(1);
	cmd->fdinopen = redirections_in(cmd);
	cmd->fdoutopen = redirections_out(cmd);
	if (cmd->fdinopen > 0)
		close(cmd->fdinopen);
	if (cmd->fdoutopen > 0)
		close(cmd->fdoutopen);
	if (cmd->fdinopen == -5)
		cmd->exit_val = 130;
	else
		command_exec(cmd, env, data);
	dup2(data->fdsave[1], 1);
	dup2(data->fdsave[0], 0);
	close(data->fdsave[1]);
	close(data->fdsave[0]);
}
