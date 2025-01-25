/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:31:53 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:19 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("The result of your function is:\n");
	printf("%i\n", ft_isascii('a'));
	printf("%i\n", ft_isascii('\0'));
	printf("%i\n", ft_isascii('?'));
	printf("%i\n", ft_isascii((char)127));
	printf("%i\n", ft_isascii((char)155));
	printf("The result of the original function is:\n");
	printf("%i\n", isascii('a'));
	printf("%i\n", isascii('\0'));
	printf("%i\n", isascii('?'));
	printf("%i\n", isascii((char)127));
	printf("%i\n", isascii((char)155));
}*/
