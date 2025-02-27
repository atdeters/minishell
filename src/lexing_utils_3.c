/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:24:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/27 18:23:35 by adeters          ###   ########.fr       */
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
		return (free(*word), *word = NULL, 0);
	if (!*word)
		return (*word = NULL, 0);
	*current = create_token(DOLAR_SIGN, *word);
	return (1);
}

/**
 * TO VOVA
 * 
 * I changed this line:
 * 	*word = ft_substr(input, j, *i - j + 1);
 * To this line:
 * 	*word = ft_substr(input, j + 1, *i - j);
 * There was a space before the delimiter otherwise
 */
int	handle_delim(char *input, t_token **current, int *i, char **word)
{
	int	j;

	*i += 2;
	j = *i;
	while (input[*i] && input[*i + 1] && !ft_is_space(input[*i + 1])
		&& input[*i + 1] != '<' && input[*i + 1] != '>'
		&& input[*i + 1] != '|' && input[*i + 1] != '$'
		&& input[*i + 1] != '\"' && input[*i + 1] != '\'')
		(*i)++;
	*word = ft_substr(input, j + 1, *i - j);
	if (!*word)
		return (*word = NULL, 0);
	*current = create_token(DELIMITER, *word);
	return (1);
}
