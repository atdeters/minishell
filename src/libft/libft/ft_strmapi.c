/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:08:58 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:59 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*ptr;
	int			i;
	int			len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s);
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}
/*
char	test_func(unsigned int i, char c)
{
	c = c + (i % 2);
	return (c);
}

#include <stdio.h>

int	main(void)
{
	char *s = "Hello World!";
	printf("%s\n", ft_strmapi(s, test_func));
}*/
