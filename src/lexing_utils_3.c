/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:24:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/11 14:08:21 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	ft_is_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f'
		|| ch == '\r')
		return (1);
	return (0);
}

int	handle_dolar(char *input, t_token **current, int *i, char **word)
{
	int	j;

	j = ++(*i);
	while (input[*i] && !ft_is_space(input[*i]) && input[*i + 1] != '$')
		(*i)++;
	*word = ft_substr(input, j, *i - j + 1);
	if (ft_strnstr(*word, "|><", ft_strlen(*word)))
		return (free(*word), 0);
	if (!*word)
		return (*word = NULL, 0);
	*current = create_token(DOLAR_SIGN, *word);
	return (1);
}
