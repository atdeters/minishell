/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:13:22 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:35 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_str_toupper(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
	char str[50] = "HellO WoRld!";
	printf("%s\n", ft_str_toupper(str));
}
*/