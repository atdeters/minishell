/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:03:43 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:00 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	if (!dest || !src)
		return (NULL);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char dest[20] = "Hello!!!";
	char src[20] = "Gfrast";
	char *point = (char *)ft_memcpy(dest, (void *)0, 6);
	printf("%s\n", dest);
}*/