/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:51:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/01/27 17:19:27 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (i == n)
		return (0);
	while (str1[i] == str2[i] && str1[i] != '\0' && i < n - 1)
	{
		i++;
	}
	if (str1[i] == str2[i])
		return (0);
	else
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
