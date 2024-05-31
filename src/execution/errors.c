/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:02:42 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_cmd_slash(t_cmd *command, char **envp, t_cmd *start)
{
	if (command->path_cmd == 0 && ft_strchr(command->cmd[0], '/') != 0)
	{
		errno = ENOENT;
		perror(command->cmd[0]);
		free_list(&start);
		free_char_tab(envp);
		exit(EXIT_FAILURE);
	}
}

static void	is_a_directory(t_cmd *command, char **envp, t_cmd *start)
{
	if (command->path_cmd)
	{
		if (command->path_cmd[ft_strlen(command->path_cmd) - 1] == '/')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command->path_cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free_list(&start);
			free_char_tab(envp);
			exit(126);
		}
	}
}

static void	no_such_file_or_directory(t_cmd *cmd, char **envp, t_cmd *start)
{
	struct stat	sb;
	int			is_directory;

	if (cmd->path_cmd)
	{
		if (stat(cmd->path_cmd, &sb) == 0)
			is_directory = S_ISDIR(sb.st_mode);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->path_cmd);
			free_list(&start);
			free_char_tab(envp);
			exit(127);
		}
		if (is_directory)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->path_cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free_list(&start);
			free_char_tab(envp);
			exit(126);
		}
	}
}

static void	command_not_found(t_cmd *command, char **envp, t_cmd *start)
{
	full_path_error(command);
	if (!command->path_cmd)
	{	
		ft_putstr_fd(command->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_list(&start);
		free_char_tab(envp);
		exit(127);
	}
}

void	error_managing(t_cmd *command, char **envp, t_cmd *start)
{
	if (command->cmd == NULL)
	{
		if (command->fdinopen != -1)
			close(command->fdinopen);
		if (command->fdoutopen != -1)
			close(command->fdoutopen);
		free_list(&start);
		free_char_tab(envp);
		exit(1);
	}
	no_cmd_slash(command, envp, start);
	is_a_directory(command, envp, start);
	no_such_file_or_directory(command, envp, start);
	command_not_found(command, envp, start);
}
