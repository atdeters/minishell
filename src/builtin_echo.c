/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:44:09 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 15:13:45 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_echo_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **command)
{
	int		i;
	bool	flag;

	i = 1;
	flag = check_echo_flag(command[i]);
	if (flag)
		i++;
	while (command[i])
	{
		ft_printf("%s", command[i]);
		i++;
		if (command[i])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}
