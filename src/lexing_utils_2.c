/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:03 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/10 19:54:28 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	handle_special_char(char *input, t_token **current, int *i)
{
	if (input[*i] == '$')
		*current = create_token(DOLAR_SIGN, NULL);
	else if (input[*i] == '|')
		*current = create_token(PIPE, NULL);
	else if (input[*i] == '<')
		*current = create_token(REDIR_IN, NULL);
	else if (input[*i] == '>')
		*current = create_token(REDIR_OUT, NULL);
	if (!(*current))
		return (0);
	return (1);
}

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
	*current = create_token(WORD, word);
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
	*current = create_token(WORD, word);
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
	while (input[*i] && !ft_is_space(input[*i]) && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '$' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
		(*i)++;
	word = ft_substr(input, start, (*i) - start);
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
