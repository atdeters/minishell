/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:03 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/18 16:56:40 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

// Moved here because of norminette
// if (input[*i] == '$')
// 	return (handle_dolar(input, current, i, &word));
int	handle_special_char(char *input, t_token **current, int *i)
{
	char	*word;

	word = NULL;
	if (input[*i] == '|')
		*current = create_token(PIPE, NULL);
	else if (input[*i] == '<' && input[*i + 1] != '<')
		*current = create_token(REDIR_IN, NULL);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (handle_delim(input, current, i, &word));
	else if (input[*i] == '>' && input[*i + 1] != '>')
		*current = create_token(REDIR_OUT, NULL);
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		*current = create_token(REDIR_APPEND, NULL);
	}
	if (!(*current))
		return (free(word), 0);
	return (1);
}

// shoud return (some error code in case of unclosed quote?
// (if (!input[*i])
// return (0));)
// should think about every error code in case of not closed quote
int	handle_single_quote(int *i, char *input, t_token **current)
{
	int		start;
	char	*word;

	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
		return (0);
	word = ft_substr(input, start, (*i) - start);
	if (!word)
		return (0);
	*current = create_token(SINGLE_QOUTE, word);
	if (!*current)
	{
		free(word);
		return (0);
	}
	(*i)++;
	return (1);
}

int	handle_nested_double_quotes(int *i, char *input, t_token **current)
{
	int		start;
	char	*word;
	char	*tmp;

	if (input[*i] == '\"')
	{
		start = ++(*i);
		while (input[*i] && input[*i] != '\"')
			(*i)++;
		if (!input[*i])
			return (0);
		word = ft_substr(input, start, (*i) - start);
		if (!word)
			return (0);
		tmp = (*current)->value;
		(*current)->value = ft_strjoin(tmp, word);
		free(tmp);
		if (!(*current)->value)
		{
			free(word);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

int	handle_double_quotes(int *i, char *input, t_token **current)
{
	int		start;
	char	*word;

	start = ++(*i);
	while (input[*i] && input[*i] != '\"')
		(*i)++;
	if (!input[*i])
		return (0);
	word = ft_substr(input, start, (*i) - start);
	if (!word)
		return (0);
	*current = create_token(DOUBLE_QOUTE, word);
	if (!*current)
	{
		free(word);
		return (0);
	}
	(*i)++;
	return (handle_nested_double_quotes(i, input, current));
}

int	handle_word(int *i, char *input, t_token **current)
{
	int		start;
	char	*word;

	start = *i;
	while (is_word_char(*i, input))
		(*i)++;
	word = ft_substr(input, start, (*i) - start + 1);
	if (!word)
		return (0);
	*current = create_token(WORD, word);
	if (!*current)
	{
		free(word);
		return (0);
	}
	return (1);
}
