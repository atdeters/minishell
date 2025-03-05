/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:07:55 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 20:37:15 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_num_str(char *str)
{
	int		i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' && str[i] > '9') && str[i] != '+' && str[i] != '-')
			return (false);
		i++;
	}
	return (true);
}

// Make this one actually check properly
bool	check_lloverflow(const char *str)
{
	if (ft_strlen(str) > 19)
		return (true);
	return (false);
}

long long int	ft_llatoi(const char *nptr)
{
	int				sign;
	long long int	nmb;
	int				i;

	sign = 1;
	nmb = 0;
	i = 0;
	if (check_lloverflow(nptr))
		return (-1);
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nmb = nmb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nmb * sign);
}

int	count_opts(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

/**
 * Exits the program with a warning that exit was used wrongly
 * aka it didn't get a numeric argument
 */
void	exit_err_nums(t_data *data, char **command)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd(EXIT_ERR_IDENT, 2);
	ft_putstr_fd(command[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ERR_MSG_EXIT_NUMS, 2);
	rage_quit(data, ERR_EXIT_USAGE, true, NULL);
}

void	ft_exit(t_data *data, char **command)
{
	int	code;

	ft_printf("exit\n");
	if (!command[1])
		rage_quit(data, 0, true, NULL);
	if (is_num_str(command[1]) && count_opts(command) == 2)
	{
		if (!ft_strcmp("-9223372036854775808", command[1]))
			rage_quit(data, 0, true, NULL);
		else
			code = ft_llatoi(command[1]) % 256;
		if (code == -1)
			exit_err_nums(data, command);
		rage_quit(data, code, true, NULL);
	}
	else if (!is_num_str(command[1]))
		exit_err_nums(data, command);
	if (count_opts(command) > 2)
	{
		ft_putstr_fd(SHELL_ERR_IDENT, 2);
		ft_putstr_fd(ERR_MSG_EXIT_ARGS, 2);
		data->exit_status = ERR_EXIT_USAGE;
		return ;
	}
}
