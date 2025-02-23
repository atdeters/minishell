/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:19:25 by adeters           #+#    #+#             */
/*   Updated: 2025/02/23 21:13:22 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_slash(char *path)
{
	int	i;
	int	counter;

	if (!path)
		return (0);
	i = 0;
	counter = 0;
	while (path[i])
	{
		if (path[i] == '/')
			counter++;
		i++;
	}
	return (counter);
}

int	ft_strcat(char *dst, const char *src)
{
	int		i;
	int		src_len;
	size_t	k;

	if (!dst || !src)
		return (-1);
	i = 0;
	src_len = 0;
	k = 0;
	while (dst[i])
		i++;
	while (src[src_len])
		src_len++;
	while (src[k])
	{
		dst[i + k] = src[k];
		k++;
	}
	return (i + src_len);
}

char	*rid_of_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (str);
}

int	ft_strcpy(char *dest, const char *src)
{
	int	i;
	int	y;

	if (!dest || !src)
		return (-1);
	i = 0;
	y = 0;
	while (src[y])
		y++;
	while (i < y)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (y);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}