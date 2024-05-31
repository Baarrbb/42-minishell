/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:27:00 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:03:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_ourenv(char *tofind, char **ourenv, char *sortie)
{
	int	i;

	i = 0;
	if (ourenv)
	{
		while (ourenv[i])
		{
			if (ft_strncmp(ourenv[i], tofind, ft_strlen(tofind)) == 0)
				return (ft_strdup(&ourenv[i][ft_strlen(tofind)]));
			i++;
		}
	}
	if (ft_strncmp(tofind, "?=\0", ft_strlen(tofind) + 1) == 0)
	{
		return (ft_strdup(sortie));
	}
	return (NULL);
}

static void	handle_on_redir(t_cmd *cmd, char *exit, char **env)
{
	t_redir	*tmp_redir;
	char	*tmp;

	if (cmd->redir)
	{
		tmp_redir = cmd->redir;
		while (tmp_redir)
		{
			tmp = tmp_redir->filename;
			if (tmp)
			{
				if (tmp_redir->in_read)
				{
					if (ft_strchr(tmp, '"') || ft_strchr(tmp, '\''))
						tmp_redir->in_quote = 1;
				}
				else
				{
					tmp_redir->e_filen = interpret_env(tmp, env, exit);
				}
				tmp_redir = tmp_redir->next;
			}
		}
	}
}

static int	handle_arg_null(char ***old, int i)
{
	int		j;
	char	**new;
	int		k;

	j = i + 1;
	while ((*old)[j])
		j++;
	new = ft_calloc(j, sizeof(char *));
	if (!new)
		return (0);
	j = -1;
	k = 0;
	while ((*old)[++j])
		new[k++] = ft_strdup((*old)[j]);
	j = i;
	while ((*old)[++j])
	{
		new[k++] = ft_strdup((*old)[j]);
		free((*old)[j]);
	}
	free_char_tab(*old);
	*old = new;
	return (1);
}

static int	handle_on_cmd(t_cmd *cmd, char **env, char *exit)
{
	int		i;
	char	*tmp;

	i = -1;
	i = -1;
	while (cmd->cmd[++i])
	{
		tmp = cmd->cmd[i];
		if (tmp)
		{
			cmd->cmd[i] = get_var_env(cmd, tmp, env, exit);
			free(tmp);
		}
		if (!cmd->cmd[i] && cmd->cmd[i + 1])
		{
			if (!handle_arg_null((&cmd->cmd), i))
				return (0);
			i--;
		}
	}
	return (1);
}

int	handle_quoting(t_cmd *cmd, char **env, int *sortie)
{
	char	*exit;

	while (cmd)
	{
		exit = ft_itoa(*sortie);
		if (cmd->cmd)
			handle_on_cmd(cmd, env, exit);
		handle_on_redir(cmd, exit, env);
		free(exit);
		cmd = cmd->next;
	}
	return (1);
}
