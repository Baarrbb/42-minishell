/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:32:00 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redir(t_redir *ptr, int *fd, int *sortie)
{
	*sortie = 1;
	(void)*fd;
	if (*fd > 0)
		close(*fd);
	ft_putstr_fd("minishell: ", 2);
	if (ptr->filename)
		ft_putstr_fd(ptr->filename, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

static void	count_space_utils(char *ptr, int i, int *w, int *inquote)
{
	if (ptr[i] == ' ' && *inquote == 0)
		(*w)++;
	if (ptr[i] == '"' && *inquote == 0)
		*inquote = 1;
	else if (ptr[i] == '\'' && *inquote == 0)
		*inquote = 2;
	else if (ptr[i] == '\'' && *inquote == 2)
		*inquote = 0;
	else if (ptr[i] == '"' && *inquote == 1)
		*inquote = 0;
}

int	count_space(t_redir *ptr, int *fd, int *sortie)
{
	int	i;
	int	j;
	int	w;
	int	inquote;

	w = 0;
	i = -1;
	j = 0;
	inquote = 0;
	if (ptr->filename)
	{
		while (ptr->filename[++i])
			count_space_utils(ptr->filename, i, &j, &inquote);
	}
	i = -1;
	inquote = 0;
	if (ptr->e_filen)
	{
		while (ptr->e_filen[++i])
			count_space_utils(ptr->e_filen, i, &w, &inquote);
	}
	if (w != j)
		return (ambiguous_redir(ptr, fd, sortie), 0);
	return (2);
}

void	expand_remove_quotes(t_cmd cmd, char *exit, char **envp, t_redir *ptr)
{
	free(ptr->e_filen);
	ptr->e_filen = get_var_env(&cmd, ptr->filename, envp, exit);
}
