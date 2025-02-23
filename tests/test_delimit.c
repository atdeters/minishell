/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_delimit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:16 by adeters           #+#    #+#             */
/*   Updated: 2025/02/23 15:56:17 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*delimiter_add_nl(char *delimiter_old)
{
	char	*delimiter;
	int		size;

	size = ft_strlen(delimiter_old) + 2;
	delimiter = ft_calloc(sizeof(char), size);
	if (!delimiter)
		return (NULL);
	ft_strlcpy(delimiter, delimiter_old, size - 1);
	delimiter[size - 2] = '\n';
	return (delimiter);
}

int	main(void)
{
	char old[] = "thisisold";
	char *new = delimiter_add_nl(old);
	ft_printf("I am old: %s", old);
	ft_printf("I am new: %s", new);
	free (new);
}