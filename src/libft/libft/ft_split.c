/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:50:08 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:51:27 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_arr_len(char const *s, char c);
static void	ft_free_all(char **arr, int index, int arr_len);
static int	ft_allo_and_copy(char **arr, int arr_len, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	int		arr_len;
	char	**arr;

	arr_len = ft_arr_len(s, c);
	arr = (char **)malloc((1 + arr_len) * sizeof(char *));
	if (arr == 0)
		return (0);
	arr[arr_len] = 0;
	if (!ft_allo_and_copy(arr, arr_len, s, c))
		return (0);
	return (arr);
}

static int	ft_arr_len(char const *s, char c)
{
	int	counter;
	int	check;
	int	i;
	int	j;

	counter = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		check = 0;
		while (s[i + j] && s[i + j] == (unsigned char)c)
			j++;
		while (s[i + j] && s[i + j] != (unsigned char)c)
		{
			j++;
			check = 1;
		}
		i = i + j;
		if (check)
			counter++;
	}
	return (counter);
}

static int	ft_allo_and_copy(char **arr, int arr_len, char const *s, char c)
{
	int	index;
	int	i;
	int	j;

	index = 0;
	i = 0;
	while (s[i] && index < arr_len)
	{
		while (s[i] == c && s[i])
			i++;
		j = 0;
		while (s[i + j] != c && s[i + j])
			j++;
		arr[index] = (char *)malloc(j * sizeof(char) + 1);
		if (arr[index] == 0)
		{
			ft_free_all(arr, index, arr_len);
			return (0);
		}
		ft_strlcpy(arr[index], &s[i], j + 1);
		i = i + j;
		index++;
	}
	return (1);
}

static void	ft_free_all(char **arr, int index, int arr_len)
{
	free(arr[arr_len]);
	if (index != 0)
	{
		index = index - 1;
		while (index >= 0)
		{
			free(arr[index]);
			index--;
		}
		free(arr);
	}
	else
	{
		free(arr[0]);
		free(arr);
	}
}
/* 
#include <stdio.h>

int	main(void)
{
	//char *s = ",,,,,hello,,,,,,,,,,,there,my,frend,,,,,";
	char **arr = ft_split(",,,,,,aa,,,,bbb,,,,,", ',');
	//printf("%i\n", ft_arr_len(s, ','));
	printf("%s\n", arr[0]);
	printf("%s\n", arr[1]);
	printf("%s\n", arr[2]);
	//printf("%s\n", arr[4]);
	//ft_free_all(arr, 4, 4);
} */
