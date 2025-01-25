/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:13:20 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:31 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_str_tolower(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
	char str[50] = "HellO WoRld!";
	printf("%s\n", ft_str_tolower(str));
}
*/