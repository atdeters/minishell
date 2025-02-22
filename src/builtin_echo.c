/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:44:09 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 17:47:00 by adeters          ###   ########.fr       */
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

void	ft_echo(char **arr)
{
	int		i;
	bool	flag;

	i = 1;
	flag = check_echo_flag(arr[i]);
	if (flag)
		i++;
	while (arr[i])
	{
		ft_printf("%s", arr[i]);
		i++;
		if (arr[i])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
}
