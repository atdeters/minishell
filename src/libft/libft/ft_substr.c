/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:55:16 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:52:19 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	s_len;
	size_t	i;
	char	*ptr;

	if (!s)
		return (NULL);
	sub_len = 0;
	i = 0;
	s_len = ft_strlen(s);
	while (s[sub_len] && sub_len < len && (sub_len + start) < s_len)
		sub_len++;
	ptr = (char *)malloc((sub_len + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	ptr[sub_len] = '\0';
	while (i < sub_len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	return (ptr);
}
/* 
int	main(void)
{
	char *s = "Ernährungsexperte";
	printf("%s\n", ft_substr(s, 9, 10));
} */