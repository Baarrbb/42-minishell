/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:01:53 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(char **envp)
{
	char	**path;
	char	**del_path;
	int		i;

	i = -1;
	path = 0;
	del_path = 0;
	if (!envp)
		return (0);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			del_path = ft_split(envp[i], '=');
			if (!del_path)
				return (0);
			path = ft_split(del_path[1], ':');
			if (!path)
				return (free_char_tab(del_path), NULL);
			break ;
		}
	}
	if (del_path)
		free_char_tab(del_path);
	return (path);
}

static int	get_max_len(char *cmd, char *cmp)
{
	int	len;

	if (ft_strlen(cmd) < ft_strlen(cmp))
		len = ft_strlen(cmp);
	else
		len = ft_strlen(cmd);
	return (len);
}

static void	is_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return ;
	if (!ft_strncmp(cmd->cmd[0], "echo", get_max_len(cmd->cmd[0], "echo")))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->cmd[0], "cd", get_max_len(cmd->cmd[0], "cd")))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->cmd[0], "pwd", get_max_len(cmd->cmd[0], "pwd")))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->cmd[0], "export",
			get_max_len(cmd->cmd[0], "export")))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->cmd[0], "unset",
			get_max_len(cmd->cmd[0], "unset")))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->cmd[0], "env", get_max_len(cmd->cmd[0], "env")))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->cmd[0], "exit", get_max_len(cmd->cmd[0], "exit")))
		cmd->builtin = 1;
}

static char	*check_exist_cmd(char *cmd1, t_cmd *cmd)
{
	int		i;
	char	*full_cmd;

	if (!cmd->path)
		return (0);
	if (!cmd1)
		return (0);
	if (cmd1[0] == '/')
		return (0);
	full_cmd = 0;
	i = -1;
	while (cmd->path[++i])
	{
		full_cmd = strjoin(full_cmd, cmd->path[i]);
		full_cmd = strjoin(full_cmd, "/");
		full_cmd = strjoin(full_cmd, cmd1);
		if (access(full_cmd, X_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		full_cmd = 0;
	}
	return (NULL);
}

int	fill_struct(t_cmd **pipe, char **args, char **envp, int *sortie)
{
	t_cmd	*tmp;

	fill_cmd(pipe, args);
	tmp = *pipe;
	if (!handle_quoting(tmp, envp, sortie))
		return (printf("Error on allocation\n"), 0);
	while (tmp)
	{
		tmp->path = get_path(envp);
		if (tmp->cmd && tmp->env_quote == tmp->is_env && tmp->cmd_quote)
			tmp->path_cmd = check_exist_cmd(tmp->cmd[0], tmp);
		else if (tmp->cmd && tmp->quote_null)
			tmp->path_cmd = check_exist_cmd(tmp->cmd[0], tmp);
		else if (tmp->cmd)
		{
			tmp->cmd = new_cmd(tmp);
			tmp->path_cmd = check_exist_cmd(tmp->cmd[0], tmp);
		}
		is_builtin(tmp);
		tmp = tmp->next;
	}
	free_char_tab(args);
	return (1);
}
