/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:29:36 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:57 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (i < n && s1_ptr[i] == s2_ptr[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return (s1_ptr[i] - s2_ptr[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "ABD";
	char *s2 = "ABC";
	printf("%i\n", ft_memcmp(s1, s2, 3));
}*/