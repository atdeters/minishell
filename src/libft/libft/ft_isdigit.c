/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:16:44 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:21 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c1 = '0';
	char c2 = '5';
	char c3 = 'A';
	char c4 = '?';
	
	printf("The result of your function is:\n");
	printf("%i\n", ft_isdigit(c1));
	printf("%i\n", ft_isdigit(c2));
	printf("%i\n", ft_isdigit(c3));
	printf("%i\n", ft_isdigit(c4));
	printf("The result of the original function is:\n");
	printf("%i\n", isdigit(c1));
	printf("%i\n", isdigit(c2));
	printf("%i\n", isdigit(c3));
	printf("%i\n", isdigit(c4));
}*/
