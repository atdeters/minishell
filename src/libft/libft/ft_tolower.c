/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:10:24 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:52:22 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_tolower('B'));
	printf("%c\n", ft_tolower('A'));
	printf("%c\n", ft_tolower('Z'));
	printf("%c\n", ft_tolower('a'));
	printf("%c\n", ft_tolower(' '));
	printf("%c\n", ft_tolower('?'));
	printf("%c\n", ft_tolower('5'));
}*/
