/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:17:40 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (8);
	return (0);
}

bool	is_num_str(char *str)
{
	int		i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isnum(str[i]) && str[i] != '+' && str[i] != '-')
			return (false);
		i++;
	}
	return (true);
}

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
