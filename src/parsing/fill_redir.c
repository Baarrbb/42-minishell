/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:15:17 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redir(t_cmd **cmd, char **args, int type)
{
	t_redir	*new;
	t_redir	*redir;

	redir = (*cmd)->redir;
	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_redir));
	if (type == 1)
		new->out = 1;
	else if (type == 2)
		new->out_end = 1;
	else if (type == 3)
		new->in = 1;
	else if (type == 4)
		new->in_read = 1;
	new->filename = ft_strdup(args[1]);
	ft_lstadd_back(&redir, new);
	(*cmd)->redir = redir;
}

int	is_redir(t_cmd **cmd, char **args, int i)
{
	int	j;

	j = i;
	while (args[j] && (!ft_strncmp(args[j], ">", ft_strlen(args[j]))
			|| !ft_strncmp(args[j], ">>", ft_strlen(args[j]))
			|| !ft_strncmp(args[j], "<", ft_strlen(args[j]))
			|| !ft_strncmp(args[j], "<<", ft_strlen(args[j]))))
	{
		if (!ft_strncmp(args[j], ">", ft_strlen(args[j])))
			init_redir(cmd, &args[j], 1);
		else if (!ft_strncmp(args[j], ">>", ft_strlen(args[j])))
			init_redir(cmd, &args[j], 2);
		else if (!ft_strncmp(args[j], "<", ft_strlen(args[j])))
			init_redir(cmd, &args[j], 3);
		else if (!ft_strncmp(args[j], "<<", ft_strlen(args[j])))
			init_redir(cmd, &args[j], 4);
		j += 2;
	}
	return (j - i);
	return (0);
}
