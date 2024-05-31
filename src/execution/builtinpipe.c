/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:57:40 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtinpipe(t_cmd *cmd, char ***env, t_exec *data, t_cmd *start)
{
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
		cmd->exit_val = our_exit(cmd, *env, data, start);
}
