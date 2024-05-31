/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:40:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_delimiter(t_heredoc *hd, char *filename)
{
	int		i;
	char	*tmp;

	i = 0;
	hd->quote = 0;
	while (filename[i])
	{
		if (filename[i] == '\'' || filename[i] == '\"')
			hd->quote = 1;
		i++;
	}
	tmp = remove_dollars(filename);
	hd->delimiter = remove_all_quotes_hd(tmp);
	free(tmp);
}

static int	writing_heredoc(t_heredoc hd, char *line, char **envp, char *exitt)
{
	char	*tmp;

	if (ft_strncmp(line, hd.delimiter, ft_strlen(hd.delimiter)) == 0)
	{
		if (line[ft_strlen(hd.delimiter)] == '\0')
		{
			free(line);
			return (0);
		}
	}
	if (hd.quote == 0)
	{
		tmp = line;
		line = interpret_env(tmp, envp, exitt);
		free(tmp);
	}
	write(hd.pipe[1], line, ft_strlen(line));
	write(hd.pipe[1], "\n", 1);
	free(line);
	return (1);
}

static void	free_heredoc(t_heredoc *hd, t_cmd *cmd, char **envp, char *exitt)
{
	close(hd->pipe[1]);
	free_list(&cmd);
	free_char_tab(envp);
	free(hd->delimiter);
	free(exitt);
}

static void	reading_heredoc(t_heredoc *hd, t_cmd *cmd, char **envp, char *exitt)
{
	char	*line;

	close(hd->pipe[0]);
	while (1)
	{
		line = readline("heredoc : ");
		if (g_sigint_received == 257)
		{
			free_heredoc(hd, cmd, envp, exitt);
			exit(124);
		}
		if (line == NULL)
		{
			ft_putstr_fd("ctrld\n", 2);
			break ;
		}
		if (writing_heredoc(*hd, line, envp, exitt) == 0)
			break ;
	}
	free_heredoc(hd, cmd, envp, exitt);
	exit(0);
}

int	heredoc(t_redir *redir, t_liberate to_free)
{
	t_heredoc	heredoc;
	int			status;

	parsing_delimiter(&heredoc, redir->filename);
	if (pipe(heredoc.pipe) < 0)
		return (perror("fail pipe heredoc"), -1);
	heredoc.pid = fork();
	if (heredoc.pid == 0)
	{
		signal(SIGINT, heredoc_sig_handler);
		reading_heredoc(&heredoc, to_free.start, to_free.env, to_free.exit);
	}
	if (heredoc.pid > 0)
	{
		sig_ignore();
		close(heredoc.pipe[1]);
		waitpid(heredoc.pid, &status, 0);
		free(heredoc.delimiter);
		if (WIFEXITED(status) && WEXITSTATUS(status))
			return (close(heredoc.pipe[0]), -5);
		return (heredoc.pipe[0]);
	}
	return (-1);
}
