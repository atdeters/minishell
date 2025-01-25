/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:54:07 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:54 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "/|\x12\xff\x09\x42\2002\42|\\";
	char *ptr = ft_memchr(s, '\200', 10);
	printf("%s\n", ptr);
}*/