/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:07:46 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:52:04 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	if (!big || !little)
		return (NULL);
	i = 0;
	if (little[i] == '\0')
		return ((char *)&big[i]);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>

int	main(void)
{
	char *big = "MZIRIBMZIRIBMZE123";
	char *little = "MZIRIBMZE";
	char *test = ft_strnstr(big, little, 9);
	if (test == 0)
		printf("%s\n", "(null)");
	else
		printf("%s\n", test);
} */