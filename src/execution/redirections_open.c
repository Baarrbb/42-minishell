/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_open.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:20:22 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file_out(t_redir *redir, int *fd)
{
	if (redir->out)
	{
		if (*fd > 2)
			close(*fd);
		*fd = open(redir->e_filen, (0100 | 02 | 01000), (S_IRUSR | S_IWUSR));
	}
	else if (redir->out_end)
	{
		if (*fd > 2)
			close(*fd);
		*fd = open(redir->e_filen, (01 | 02000 | 0100), (S_IRUSR | S_IWUSR));
	}
}

void	open_file_in(t_redir *redir, int *fd)
{
	if (redir->in)
	{
		if (*fd > 2)
			close(*fd);
		*fd = open(redir->e_filen, O_RDONLY, (S_IRUSR | S_IWUSR));
	}
	else if (redir->in_read)
	{
		if (*fd > 2)
			close(*fd);
		*fd = redir->fdhd;
	}
}

int	open_tests(t_redir *ptr, int *fd, int *sortie)
{
	if (ptr->in)
		*fd = open(ptr->e_filen, O_RDONLY, (S_IRUSR | S_IWUSR));
	else if (ptr->out)
		*fd = open(ptr->e_filen, (0100 | 02 | 01000), (S_IRUSR | S_IWUSR));
	else if (ptr->out_end)
		*fd = open(ptr->e_filen, (01 | 02000 | 0100), (S_IRUSR | S_IWUSR));
	if (*fd == -1)
	{
		*sortie = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(ptr->e_filen);
		if (*fd > 0)
			close(*fd);
		return (0);
	}
	return (1);
}
