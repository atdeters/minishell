/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:07:55 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 15:24:32 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_err_nums(t_data *data, char **command)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd(EXIT_ERR_IDENT, 2);
	ft_putstr_fd(command[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ERR_MSG_EXIT_NUMS, 2);
	rage_quit(data, ERR_BUILTIN_USAGE, true, NULL);
}

int	check_exit_args(char **command)
{
	if (count_opts(command) > 2)
	{
		ft_putstr_fd(SHELL_ERR_IDENT, 2);
		ft_putstr_fd(ERR_MSG_EXIT_ARGS, 2);
		return (ERR_BUILTIN_USAGE);
	}
	return (0);
}

int	ft_exit(t_data *data, char **command)
{
	long long int	code;

	code = 0;
	ft_putstr_fd("exit\n", 2);
	if (!command[1])
		rage_quit(data, 0, true, NULL);
	if (is_num_str(command[1]) && count_opts(command) == 2)
	{
		if (!ft_strcmp("-9223372036854775808", command[1]))
			rage_quit(data, 0, true, NULL);
		else if (lloverflow(command[1]))
			exit_err_nums(data, command);
		else
			code = ft_atoll(command[1]) % 256;
		data->p_err = false;
		rage_quit(data, code, true, NULL);
	}
	if (!is_num_str(command[1]))
		exit_err_nums(data, command);
	return (check_exit_args(command));
}
