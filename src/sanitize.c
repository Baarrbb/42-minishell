/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:33:59 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = -1;
	if (*tab)
	{
		while (tab[++i])
			free(tab[i]);
	}
	if (tab)
		free(tab);
}

static void	free_redir(t_redir **redir)
{
	t_redir	*tmp;

	if (redir)
	{
		while (*redir)
		{
			tmp = (*redir)->next;
			free((*redir)->filename);
			if ((*redir)->e_filen)
				free((*redir)->e_filen);
			if ((*redir)->fdhd > 2)
				close((*redir)->fdhd);
			free(*redir);
			*redir = tmp;
		}
	}
	*redir = 0;
}

void	free_list(t_cmd **list)
{
	t_cmd	*tmp;

	if (list)
	{
		while (*list)
		{
			if ((*list)->path)
				free_char_tab((*list)->path);
			if ((*list)->cmd)
				free_char_tab((*list)->cmd);
			free_redir(&((*list)->redir));
			free((*list)->path_cmd);
			if ((*list)->fdinopen > 2)
				close((*list)->fdinopen);
			if ((*list)->fdoutopen > 2)
				close((*list)->fdoutopen);
			tmp = (*list)->next;
			free(*list);
			*list = tmp;
		}
		*list = 0;
	}
	else
		free_redir(&((*list)->redir));
}

void	free_struct_exec(t_exec *data)
{
	free(data->pipefds);
	free(data->pid);
	if (data->builtin)
	{
		free(data->builtin);
	}
	free(data);
}
