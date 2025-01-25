/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:39:29 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:29:06 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"

int	ft_putnbr_base_fd(long long nbr, char *base, int fd)
{
	int	bytes_written;

	if (nbr == (long long)ULONG_MAX)
	{
		write(fd, "ffffffffffffffff", 16);
		return (16);
	}
	if (nbr < 0)
		nbr = nbr * -1;
	if (nbr == 0)
	{
		write(fd, &base[0], 1);
		return (1);
	}
	if (nbr / 16 == 0)
	{
		write(fd, &base[nbr % 16], 1);
		return (bytes_written = 1);
	}
	bytes_written = ft_putnbr_base_fd(nbr / 16, base, fd)
		+ ft_putnbr_base_fd(nbr % 16, base, fd);
	return (bytes_written);
}
