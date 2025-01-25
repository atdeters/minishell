/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:43:19 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:27 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_bytes(int n);
static int	check_int_min(int n);
static int	min_switch(int *n, int *i, char *ptr);
static char	*ft_strcpy(char *dest, const char *src, int size);

char	*ft_itoa(int n)
{
	char	*ptr;
	int		bytes;
	int		i;
	int		check_pos;

	i = 0;
	bytes = ft_count_bytes(n);
	check_pos = 2;
	ptr = (char *)malloc (bytes * sizeof(char));
	if (ptr == 0)
		return (0);
	if (check_int_min(n))
		return (ft_strcpy(ptr, "-2147483648", 12));
	if (n < 0)
		check_pos = min_switch(&n, &i, ptr);
	ptr[bytes - 1] = '\0';
	while (i < (bytes - 1))
	{
		ptr[bytes - check_pos - i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	return (ptr);
}

static char	*ft_strcpy(char *dest, const char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_count_bytes(int n)
{
	int	digits;

	digits = 1;
	if (n <= 0)
		digits = 2;
	while (n)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

static int	check_int_min(int n)
{
	if (n == -2147483648)
		return (1);
	return (0);
}

static int	min_switch(int *n, int *i, char *ptr)
{
	*i = 1;
	*n = *n * (-1);
	ptr[0] = '-';
	return (1);
}
/*
#include <stdio.h>

int main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(-2147483647));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-42));
	printf("%s\n", ft_itoa(42));
}*/