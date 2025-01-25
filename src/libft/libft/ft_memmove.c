/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:12:53 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:03 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (dest > src)
	{
		while (i < n)
		{
			dest_ptr[(n - 1) - i] = src_ptr[(n - 1) - i];
			i++;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char dest[240];
	memset(dest, 'A', 240);
	printf("%s\n", (char *)ft_memmove(dest, dest, 225));
	memset(dest, '\0', 210);
	char dest1[240];
	memset(dest1, 'A', 240);
	printf("%s\n", (char *)memmove(dest1, dest1, 225));
	memset(dest1, '\0', 210);
}*/