/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:43:33 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:22 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_chars(int n);

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr[10];
	int		chars;
	int		i;
	int		first_ind;
	long	long_n;

	long_n = (long)n;
	chars = ft_count_chars(long_n);
	first_ind = 10 - chars;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n = long_n * (-1);
	}
	i = 0;
	if (long_n == 0)
		write (fd, "0", 1);
	while (long_n > 0)
	{
		nbr[(first_ind + (chars - 1)) - i] = long_n % 10 + '0';
		long_n = long_n / 10;
		i++;
	}
	write(fd, &nbr[first_ind], chars);
}

static int	ft_count_chars(int n)
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
/*
#include <stdio.h>

int	main(void)
{
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");
	ft_putnbr_fd(2147483647, 1);
	printf("\n");
	ft_putnbr_fd(0, 1);
	printf("\n");
}*/