/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:16:45 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	overflow_digits(char *str)
{
	if (str[0] > 2 + '0')
		return (1);
	if (str[1] > 1 + '0' && ft_strncmp(str, "2147483647", 1) == 0)
		return (1);
	if (str[2] > 4 + '0' && ft_strncmp(str, "2147483647", 2) == 0)
		return (1);
	if (str[3] > 7 + '0' && ft_strncmp(str, "2147483647", 3) == 0)
		return (1);
	if (str[4] > 4 + '0' && ft_strncmp(str, "2147483647", 4) == 0)
		return (1);
	if (str[5] > 8 + '0' && ft_strncmp(str, "2147483647", 5) == 0)
		return (1);
	if (str[6] > 3 + '0' && ft_strncmp(str, "2147483647", 6) == 0)
		return (1);
	if (str[7] > 6 + '0' && ft_strncmp(str, "2147483647", 7) == 0)
		return (1);
	if (str[8] > 4 + '0' && ft_strncmp(str, "2147483647", 8) == 0)
		return (1);
	if (str[9] > 7 + '0' && ft_strncmp(str, "2147483647", 9) == 0)
		return (1);
	return (0);
}

int	underflow_digits(char *str)
{
	if (str[0] > 2 + '0')
		return (-1);
	if (str[1] > 1 + '0' && ft_strncmp(str, "2147483648", 1) == 0)
		return (-1);
	if (str[2] > 4 + '0' && ft_strncmp(str, "2147483648", 2) == 0)
		return (-1);
	if (str[3] > 7 + '0' && ft_strncmp(str, "2147483648", 3) == 0)
		return (-1);
	if (str[4] > 4 + '0' && ft_strncmp(str, "2147483648", 4) == 0)
		return (-1);
	if (str[5] > 8 + '0' && ft_strncmp(str, "2147483648", 5) == 0)
		return (-1);
	if (str[6] > 3 + '0' && ft_strncmp(str, "2147483648", 6) == 0)
		return (-1);
	if (str[7] > 6 + '0' && ft_strncmp(str, "2147483648", 7) == 0)
		return (-1);
	if (str[8] > 4 + '0' && ft_strncmp(str, "2147483648", 8) == 0)
		return (-1);
	if (str[9] > 8 + '0' && ft_strncmp(str, "2147483648", 9) == 0)
		return (-1);
	return (0);
}

char	*ignore_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
	{
		*sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (NULL);
	while (str[i] && str[i] == '0')
		i++;
	return (&str[i]);
}

int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-2);
		i++;
	}
	return (0);
}

int	check_overflow(char *str)
{
	int		len;
	int		sign;
	char	*new;

	new = ignore_sign(str, &sign);
	if (!new || is_digit_str(new) == -2)
		return (-2);
	len = ft_strlen(new);
	if (len > 10 && sign == -1)
		return (-1);
	if (len > 10 && sign == 1)
		return (1);
	if (len < 9)
		return (0);
	if (len == 10 && sign == -1)
		return (underflow_digits(new));
	else if (len == 10)
		return (overflow_digits(new));
	return (0);
}
