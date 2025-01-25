/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:25:48 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:52:16 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static int	ft_checkset(char c, char const *set);
static int	ft_trim_strlen(char const *s1, char const *set, int start);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		size;
	int		i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	i = 0;
	while (ft_checkset(s1[start], set))
		start++;
	size = ft_trim_strlen(s1, set, start) + 1;
	ptr = (char *)malloc(size * sizeof(char));
	if (ptr == 0)
		return (0);
	while (i < (size - 1))
	{
		ptr[i] = s1[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int	ft_checkset(char c, char const *set)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (set[i])
	{
		if (c == set[i])
			check = 1;
		i++;
	}
	return (check);
}

static int	ft_trim_strlen(char const *s1, char const *set, int start)
{
	int	end;
	int	i;

	end = start;
	i = 0;
	while (s1[end])
	{
		while (!ft_checkset(s1[end], set) && s1[end])
			end++;
		i = 0;
		while (ft_checkset(s1[end + i], set) && s1[end])
		{
			if (s1[end + i + 1] == '\0')
				return (end - start);
			i++;
		}
		end += i;
	}
	return (end - start);
}
/* 
#include <stdio.h>

int	main(void)
{
	char *s = "- -.. . --Hello World----...-.-  ";
	char *set = " -.";
	printf("%s\n", ft_strtrim(s, set));
} */