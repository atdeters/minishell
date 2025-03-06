/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:07:55 by adeters           #+#    #+#             */
/*   Updated: 2025/03/06 14:07:34 by adeters          ###   ########.fr       */
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
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && str[i] != '-')
			return (false);
		i++;
	}
	return (true);
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (8);
	return (0);
}

// Make this one actually check properly
bool	lloverflow(const char *str)
{
	if (ft_strlen(str) > 20)
		return (true);
	if (ft_strlen(str) == 20 && ft_isnum(str[0]))
		return (true);
	if (ft_strlen(str) == 20 && str[0] == '-')
	{
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
			return (true);
	}
	if (ft_strlen(str) == 20 && str[0] == '+')
	{
		if (ft_strncmp(str, "+9223372036854775807", 20) > 0)
			return (true);
	}
	if (ft_strlen(str) == 19 && ft_isnum(str[0]))
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (true);
	}
	return (false);
}

long long int	ft_atoll(const char *nptr)
{
	int				sign;
	long long int	nmb;
	int				i;

	sign = 1;
	nmb = 0;
	i = 0;
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
	long long int	code;

	code = 0;
	ft_printf("exit\n");
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
		rage_quit(data, code, true, NULL);
	}
	if (!is_num_str(command[1]))
		exit_err_nums(data, command);
	if (count_opts(command) > 2)
	{
		ft_putstr_fd(SHELL_ERR_IDENT, 2);
		ft_putstr_fd(ERR_MSG_EXIT_ARGS, 2);
		data->exit_status = ERR_EXIT_USAGE;
		return ;
	}
}
