/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:52:11 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:57 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./a.out String\n");
		return (1);
	}
	
	printf("The string in argv[1] is %i character long\n", ft_strlen(argv[1]));
}*/
