/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:07:33 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

static int	execution(t_cmd *pipe, char ***cpy_env, int *sortie)
{
	if (pipe)
	{
		changevar(pipe, *cpy_env);
		pipe->last_exit_status = *sortie;
		if (check_commands(pipe, sortie) == 0)
			*sortie = start_execute(pipe, cpy_env);
		if (*sortie == -1)
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
	}
	return (1);
}

int	heredoc_check(t_cmd *pipe, char **envp, int *sortie)
{
	t_cmd		*tmpcmd;
	t_redir		*tmpr;
	char		*exitt;

	exitt = ft_itoa(*sortie);
	tmpcmd = pipe;
	while (tmpcmd)
	{
		tmpr = tmpcmd->redir;
		while (tmpr)
		{
			if (tmpr->in_read)
			{
				if (tmpr->fdhd > 0)
					close(tmpr->fdhd);
				tmpr->fdhd = heredoc(tmpr, (t_liberate){pipe, envp, exitt});
				if (tmpr->fdhd == -5)
					return (free(exitt), 1);
			}
			tmpr = tmpr->next;
		}
		tmpcmd = tmpcmd->next;
	}
	return (free(exitt), 0);
}

int	in_while(t_cmd *pipe, char ***cpy_env, int *sortie)
{
	char	*line;
	char	*prompt;

	signal_starting();
	prompt = display_prompt(*cpy_env);
	line = readline(prompt);
	rl_on_new_line();
	if (!line)
		return (printf("exit\n"), free(prompt), \
		our_exit(pipe, *cpy_env, 0, 0), 0);
	if (line[0] != 0)
		add_history(line);
	if (g_sigint_received == 2)
	{
		*sortie = 130;
		g_sigint_received = 0;
	}
	check_line(line, &pipe, *cpy_env, sortie);
	free(prompt);
	if (heredoc_check(pipe, *cpy_env, sortie) == 1)
		*sortie = 130;
	else
		if (execution(pipe, cpy_env, sortie) == 0)
			return (free_list(&pipe), 0);
	return (free_list(&pipe), 1);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*pipe;
	char	**cpy_env;
	int		sortie;

	(void)av;
	if (ac != 1)
		return (0);
	pipe = 0;
	sortie = 0;
	cpy_env = copy_env(envp);
	while (1)
	{
		if (in_while(pipe, &cpy_env, &sortie) == 0)
			break ;
	}
	free_char_tab(cpy_env);
	return (0);
}
