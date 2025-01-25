/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_retbytes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:02:09 by adeters           #+#    #+#             */
/*   Updated: 2024/09/18 14:16:35 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd_retbytes(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
	return (i);
}
