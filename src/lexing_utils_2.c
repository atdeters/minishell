/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:03 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/04 18:03:02 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * @brief Helper function to copy string without quotes
 * @param word Source string
 * @param flag Quote type flag
 * @param new_new Destination string
 */
void	transfer_str_in_rq(char *word, int flag, char *new_new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if ((word[i] != '\"' && flag == 2) || (word[i] != '\'' && flag == 1)
				|| (word[i] != '\'' && word[i] != '"') || (word[i] != '"'
				&& word[i] != '\'' && flag == 3))
			new_new[j++] = word[i];
		i++;
	}
	new_new[j] = '\0';
}

/**
 * @brief Removes quotes from a string while preserving content
 * @param word Input string containing quotes
 * @return New string with quotes removed, NULL on failure
 */
char	*remove_quotes(char *word)
{
	int		i;
	char	*new_new;
	int		j;
	int		flag;

	j = 0;
	i = 0;
	flag = 0;
	while (word[i])
	{
		if (word[i] == '\"' && !flag)
			flag = 2;
		else if (word[i] == '\'' && !flag)
			flag = 1;
		else if (word[i] == '"' && flag == 1)
			flag = 4;
		else if (word[i] == '"' && flag == 4)
			flag = 3;
		i++;
	}
	if (flag == 4)
		flag = 1;
	i = 0;
	while (word[i])
	{
		// if (word[i] == '\"' && !flag)
		// flag = 2;
		// else if (word[i] == '\'' && !flag)
			// flag = 1;
		// else if (word[i] == '"' && flag == 1)
			// flag = 3;
		if ((word[i] != '\"' && flag == 2) || (word[i] != '\'' && flag == 1)
				|| (word[i] != '\"' && word[i] != '\'') || (word[i] != '"'
				&& flag == 3))
			j++;
		i++;
	}
	new_new = malloc((j + 1) * sizeof(char));
	if (!new_new)
		return (NULL);
	transfer_str_in_rq(word, flag, new_new);
	return (new_new);
}

/**
 * @brief Iterates through word characters handling quotes
 * @param i Current position in input
 * @param input Input string
 * @return Always returns 1
 */
int	iterate_word(int *i, char *input)
{
	static int	flag = 0;

	while (is_word_char(*i, input, &flag))
	{
		if (input[*i] == '\'' && flag == 0)
			flag = 1;
		else if (input[*i] == '"' && flag == 0)
			flag = 2;
		else if (input[*i] == '\'' && flag == 1)
			flag = 0;
		else if (input[*i] == '"' && flag == 2)
			flag = 0;
		(*i)++;
	}
	flag = 0;
	return (1);
}

/**
 * @brief Handles word token creation including quote removal
 * @param i Current position in input
 * @param input Input string
 * @param current Pointer to store created token
 * @param data Shell data structure
 * @return 1 on success, 0 on failure
 */
int	handle_word(int *i, char *input, t_token **current, t_data *data)
{
	int		start;
	char	*word;
	char	*final_word;

	start = *i;
	iterate_word(i, input);
	word = ft_substr(input, start, (*i) - start + 1);
	if (!word)
		return (data->error = ERR_MALLOC, 0);
	printf("word = |%s|\n", word);
	final_word = remove_quotes(word);
	printf("finaL_word = |%s|\n", final_word);
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
