/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:24:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/08 13:45:15 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (data->input[*i] && data->input[*i + 1]
		&& !ft_is_space(data->input[*i + 1])
		&& data->input[*i + 1] != '<' && data->input[*i + 1] != '>'
		&& data->input[*i + 1] != '|' && data->input[*i + 1] != '$'
		&& data->input[*i + 1] != '\"' && data->input[*i + 1] != '\'')
		(*i)++;
	*word = ft_substr(data->input, j, *i - j + 1);
	if (!*word)
		return (*word = NULL, data->error = ERR_MALLOC, 0);
	*current = create_token(DELIMITER, *word);
	return (1);
}

/**
 * @brief Handles special characters (|, <, >, <<, >>)
 * @param input Input string
 * @param current Pointer to store created token
 * @param i Current position in input
 * @param data Shell data structure
 * @return 1 on success, 0 on failure
 */
int	handle_special_char(char *input, t_token **current, int *i, t_data *data)
{
	char	*word;

	word = NULL;
	if (input[*i] == '|')
		*current = create_token(PIPE, NULL);
	else if (input[*i] == '<' && input[*i + 1] != '<')
		*current = create_token(REDIR_IN, NULL);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		handle_delim(data, current, i, &word);
	else if (input[*i] == '>' && input[*i + 1] != '>')
		*current = create_token(REDIR_OUT, NULL);
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		*current = create_token(REDIR_APPEND, NULL);
	}
	if (!(*current))
		return (free(word), data->error = ERR_MALLOC, 0);
	return (1);
}
