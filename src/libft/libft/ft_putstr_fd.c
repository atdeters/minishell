/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:18:03 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:24 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write (fd, s, ft_strlen(s));
}
/*
int	main(void)
{
	char *str = "Hey du gfrast!";
	ft_putstr_fd(str, 1);
}*/