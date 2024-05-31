/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:03:51 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_redir
{
	int				out;
	int				out_end;
	int				in;
	int				in_read;
	int				in_quote;
	char			*filename;
	char			*e_filen;
	int				fdhd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env
{
	char	**env;
	char	**tmp;
	char	*arg;
}	t_env;

typedef struct s_cmd
{
	char			**path;
	char			**cmd;
	int				builtin;
	char			*path_cmd;
	int				exit_val;
	int				last_exit_status;
	int				var_env;
	int				cmd_quote;

	int				is_env;
	int				env_quote;
	int				quote_null;

	int				fdinopen;
	int				fdoutopen;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	t_cmd	*command;
	int		numpipes;
	int		index;
	pid_t	*pid;
	int		*builtin;
	int		*pipefds;
	int		fd;
	int		pipeindex;
	int		fdsave[2];
}	t_exec;

typedef struct s_heredoc
{
	char	*delimiter;
	int		pipe[2];
	int		quote;
	pid_t	pid;
}	t_heredoc;

typedef struct s_liberate
{
	t_cmd	*start;
	char	**env;
	char	*exit;
}	t_liberate;

#endif