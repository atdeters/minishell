/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:10:41 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:51 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		src_len;
	size_t	k;

	if (!dst || !src)
		return (-1);
	i = 0;
	src_len = 0;
	k = 0;
	while (dst[i] && i < size)
		i++;
	while (src[src_len])
		src_len++;
	if (i >= size)
		return (src_len + size);
	while (src[k] && k < (size - (i + 1)))
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (i + src_len);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char dst[15] = "Hello";
	char src[10] = " World";
	printf("%zu\n", ft_strlcat(dst, src, 15));
	printf("%s\n", dst);
	char dst1[15] = "Hello";
	char src1[10] = " World";
	printf("%zu\n", strlcat(dst1, src1, 15));
	printf("%s\n", dst1);
}*/
