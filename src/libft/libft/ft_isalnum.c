/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:22:39 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:14 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (8);
	else if (c >= 'A' && c <= 'Z')
		return (8);
	else if (c >= '0' && c <= '9')
		return (8);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c1 = 'A';
	char c2 = 'f';
	char c3 = '0';
	char c4 = '8';
	char c5 = ' ';
	char c6 = '{';
	
	
	printf("The result of your function is:\n");
	printf("%i\n", ft_isalnum(c1));
	printf("%i\n", ft_isalnum(c2));
	printf("%i\n", ft_isalnum(c3));
	printf("%i\n", ft_isalnum(c4));
	printf("%i\n", ft_isalnum(c5));
	printf("%i\n", ft_isalnum(c6));
	printf("The result of the original function is:\n");
	printf("%i\n", isalnum(c1));
	printf("%i\n", isalnum(c2));
	printf("%i\n", isalnum(c3));
	printf("%i\n", isalnum(c4));
	printf("%i\n", isalnum(c5));
	printf("%i\n", isalnum(c6));
}
*/
