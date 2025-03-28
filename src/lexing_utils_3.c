/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:24:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/28 17:23:49 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if character at position is part of a word
 * @param i Current position in input
 * @param input Input string
 * @param flag Quote status flag
 * @return true if character is part of word, false otherwise
 */
bool is_word_char(int i, char *input, int *flag);

/**
 * @brief Checks if character is a whitespace
 * @param ch Character to check
 * @return 1 if whitespace, 0 otherwise
 */
int ft_is_space(char ch);

/**
 * @brief Handles here-document delimiter token
 * @param data Shell data structure
 * @param current Pointer to store created token
 * @param i Current position in input
 * @param word Pointer to store delimiter word
 * @return 1 on success, 0 on failure
 */
int handle_delim(t_data *data, t_token **current, int *i, char **word);

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
	if ((input[i] == '"' || input[i] == '\'') && ft_is_space(input[i + 1]))
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
