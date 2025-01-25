/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:47:10 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:23 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("The result of your function is:\n");
	printf("%i\n", ft_isprint('A'));
	printf("%i\n", ft_isprint('0'));
	printf("%i\n", ft_isprint(' '));
	printf("%i\n", ft_isprint('\n'));
	printf("%i\n", ft_isprint('9'));
	printf("%i\n", ft_isprint('&'));
	printf("The result of the original function is:\n");
	printf("%i\n", isprint('A'));
	printf("%i\n", isprint('0'));
	printf("%i\n", isprint(' '));
	printf("%i\n", isprint('\n'));
	printf("%i\n", isprint('9'));
	printf("%i\n", isprint('&'));
}*/
