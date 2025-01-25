/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:39:38 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:09 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	if (s)
	{
		ptr = (char *)s;
		i = 0;
		while (i < n)
		{
			ptr[i] = '\0';
			i++;
		}
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char s[20] = "Hello World!";
	ft_bzero(NULL, 4);
	printf("%s\n", s);
}
*/