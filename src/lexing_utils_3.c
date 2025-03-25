/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:24:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/25 19:13:08 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
DONT wanna lose it
It was part of is_word_char. Now i dont need it
	// if (input[i + 1] == '\'')
	// 	return (false);
	// if (input[i + 1] == '"')
	// 	return (false);
	// if (input[i + 1] == '$')
	// 	return (false);
*/
bool	is_word_char(int i, char *input, int *flag)
{
	if (!input[i] | !input[i + 1])
		return (false);
	if (ft_is_space(input[i + 1]) && *flag)
		return (true);
	if (ft_is_space(input[i + 1]))
		return (false);
	if (input[i + 1] == '|' && !(*flag))
		return (false);
	if (input[i + 1] == '<' && !(*flag))
		return (false);
	if (input[i + 1] == '>' && !(*flag))
		return (false);
	return (true);
}

int	ft_is_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f'
		|| ch == '\r')
		return (1);
	return (0);
}

// int	handle_dolar(char *input, t_token **current, int *i, char **word)
// {
// 	int	j;

// 	j = ++(*i);
// 	while (input[*i] && !ft_is_space(input[*i]) && input[*i + 1] != '$')
// 		(*i)++;
// 	*word = ft_substr(input, j, *i - j + 1);
// 	if (ft_strnstr(*word, "|><", ft_strlen(*word)))
// 		return (free(*word), *word = NULL, 0);
// 	if (!*word)
// 		return (*word = NULL, 0);
// 	*current = create_token(DOLAR_SIGN, *word);
// 	return (1);
// }

/**
 * TO VOVA
 *
 * I changed this line:
 * 	*word = ft_substr(input, j, *i - j + 1);
 * To this line:
 * 	*word = ft_substr(input, j + 1, *i - j);
 * There was a space before the delimiter otherwise
 */
int	handle_delim(t_data *data, t_token **current, int *i, char **word)
{
	int	j;

	*i += 2;
	while (ft_is_space(data->input[*i]))
		(*i)++;
	j = *i;
	while (data->input[*i] && data->input[*i + 1] && !ft_is_space(data->input[*i
				+ 1]) && data->input[*i + 1] != '<'
		&& data->input[*i + 1] != '>'
		&& data->input[*i + 1] != '|' && data->input[*i + 1] != '$'
		&& data->input[*i + 1] != '\"' && data->input[*i + 1] != '\'')
		(*i)++;
	*word = ft_substr(data->input, j, *i - j + 1);
	if (!*word)
		return (*word = NULL, data->error = ERR_MALLOC, 0);
	*current = create_token(DELIMITER, *word);
	return (1);
}
