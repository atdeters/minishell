/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:53:03 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:16 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c1 = 'A';
	char c2 = 'Q';
	char c3 = '0';
	
	printf("The result of your functions is:\n");
	printf("%i\n", ft_isalpha(c1));
	printf("%i\n", ft_isalpha(c2));
	printf("%i\n", ft_isalpha(c3));
	printf("The result of the original functions is:\n");
	printf("%i\n", isalpha(c1));
	printf("%i\n", isalpha(c2));
	printf("%i\n", isalpha(c3));
}*/
