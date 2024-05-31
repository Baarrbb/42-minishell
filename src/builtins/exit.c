/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:42:03 by marvin            #+#    #+#             */
/*   Updated: 2024/05/31 16:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	custom_atoi(const char *str)
{
	long long			sign;
	int					i;
	unsigned long long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > (LLONG_MAX))
			return (1);
		if (sign == -1 && result > (unsigned long long)9223372036854775807 + 1)
			return (1);
		i++;
	}
	return (0);
}

static int	check_val_exit(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (i == 0 && (cmd[0] == '-' || cmd[0] == '+'))
			continue ;
		if (!ft_isdigit(cmd[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			return (1);
		}
	}
	if (custom_atoi(cmd) == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

static int	exit_utils(t_cmd *everything, int *status)
{
	if (check_val_exit(everything->cmd[1]))
		*status = 2;
	else
	{
		*status = ft_atoi(everything->cmd[1]) % 256;
		if (everything->cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			if (everything->last_exit_status == 0)
				return (1);
			return (everything->last_exit_status);
		}
	}
	return (-1);
}

static void	clean_exit(t_exec *data, char **env)
{
	free_char_tab(env);
	rl_clear_history();
	if (data)
		close_all_pipes(data->numpipes, data->pipefds);
	if (data)
		free_struct_exec(data);
}

int	our_exit(t_cmd *everything, char **env, t_exec *data, t_cmd *start)
{
	int	status;
	int	returnvalue;

	status = EXIT_SUCCESS;
	if (everything)
	{
		status = everything->last_exit_status;
		if (data->numpipes == 1)
			ft_putstr_fd("exit\n", 2);
		if (everything->cmd[1])
			returnvalue = exit_utils(everything, &status);
		if (everything->cmd[1])
			if (returnvalue != -1)
				return (returnvalue);
		if (start)
			free_list(&start);
		else
			free_list(&everything);
	}
	clean_exit(data, env);
	exit(status);
}
