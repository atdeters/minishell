/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:03 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/21 17:55:44 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Moved here because of norminette
// if (input[*i] == '$')
// 	return (handle_dolar(input, current, i, &word));

/*
	in case of malloc error in handle_delim,
		we will check it with if (!*current)
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

// shoud return (some error code in case of unclosed quote?
// (if (!input[*i])
// return (0));)
// should think about every error code in case of not closed quote
// int	handle_single_quote(int *i, char *input, t_token **current)
// {
// 	int		start;
// 	char	*word;

// 	start = ++(*i);
// 	while (input[*i] && input[*i] != '\'')
// 		(*i)++;
// 	if (!input[*i])
// 		return (0);
// 	word = ft_substr(input, start, (*i) - start);
// 	if (!word)
// 		return (0);
// 	*current = create_token(SINGLE_QOUTE, word);
// 	if (!*current)
// 	{
// 		free(word);
// 		return (0);
// 	}
// 	if (input[*i + 1] && (input[*i + 1] == ' ' || input[*i + 1] == '\''))
// 		(*i)++;
// 	return (1);
// }

// int	handle_nested_double_quotes(int *i, char *input, t_token **current)
// {
// 	int		start;
// 	char	*word;
// 	char	*tmp;

// 	if (input[*i] == '\"')
// 	{
// 		start = ++(*i);
// 		while (input[*i] && input[*i] != '\"')
// 			(*i)++;
// 		if (!input[*i])
// 			return (0);
// 		word = ft_substr(input, start, (*i) - start);
// 		if (!word)
// 			return (0);
// 		tmp = (*current)->value;
// 		(*current)->value = ft_strjoin(tmp, word);
// 		free(tmp);
// 		if (!(*current)->value)
// 		{
// 			free(word);
// 			return (0);
// 		}
// 		(*i)++;
// 	}
// 	return (1);
// }

// int	handle_double_quotes(int *i, char *input, t_token **current)
// {
// 	int		start;
// 	char	*word;

// 	start = ++(*i);
// 	while (input[*i] && input[*i] != '\"')
// 		(*i)++;
// 	if (!input[*i])
// 		return (0);
// 	word = ft_substr(input, start, (*i) - start);
// 	if (!word)
// 		return (0);
// 	*current = create_token(DOUBLE_QOUTE, word);
// 	if (!*current)
// 	{
// 		free(word);
// 		return (0);
// 	}
// 	if (input[*i + 1] && (input[*i + 1] == ' ' || input[*i + 1] == '\"'))
// 		return ((*i)++, handle_nested_double_quotes(i, input, current));
// 	return (1);
// }

char	*remove_quotes(char *word)
{
	int		i;
	char	*new_new;
	int		j;

	j = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] != '\"' && word[i] != '\'')
			j++;
		i++;
	}
	new_new = malloc((j + 1) * sizeof(char));
	if (!new_new)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] != '\"' && word[i] != '\'')
			new_new[j++] = word[i];
		i++;
	}
	new_new[j] = '\0';
	return (new_new);
}

int	handle_word(int *i, char *input, t_token **current, t_data *data)
{
	int		start;
	char	*word;
	char	*final_word;

	start = *i;
	while (is_word_char(*i, input))
		(*i)++;
	word = ft_substr(input, start, (*i) - start + 1);
	if (!word)
		return (data->error = ERR_MALLOC, 0);
	final_word = remove_quotes(word);
	free(word);
	if (!final_word)
		return (data->error = ERR_MALLOC, 0);
	*current = create_token(WORD, final_word);
	if (!*current)
	{
		free(final_word);
		return (data->error = ERR_MALLOC, 0);
	}
	return (1);
}
