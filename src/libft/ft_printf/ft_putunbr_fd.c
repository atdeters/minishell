/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:43:33 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:29:15 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_chars(unsigned int n);

int	ft_putunbr_fd(unsigned int n, int fd)
{
	char	nbr[9];
	int		chars;
	int		i;
	int		first_ind;

	chars = ft_count_chars(n);
	first_ind = 9 - chars;
	i = 0;
	if (n == 0)
	{
		write (fd, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		nbr[(first_ind + (chars - 1)) - i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	write(fd, &nbr[first_ind], chars);
	return (chars);
}

static int	ft_count_chars(unsigned int n)
{
	int	chars;

	chars = 0;
	if (n == 0)
		chars = 0;
	while (n)
	{
		n = n / 10;
		chars++;
	}
	return (chars);
}
