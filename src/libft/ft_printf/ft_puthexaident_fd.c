/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexaident.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:56 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:28:52 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexaident_fd(char code, int fd)
{
	if (code == 'x')
		write(fd, "0x", 2);
	else if (code == 'X')
		write(fd, "0X", 2);
	return (2);
}
