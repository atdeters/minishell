/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 20:08:13 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:41 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	ptr = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (i < ft_strlen((char *)s))
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char *str = "Hello World!";
	printf("%s\n", ft_strdup(str));
}*/
