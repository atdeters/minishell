/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:03 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/08 14:07:09 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_word_char(int i, char *input, int *flag)
{
	if (!input[i] | !input[i + 1])
		return (false);
	if (input[i] == '\'' && ft_is_space(input[i + 1]) && *flag == 1)
		return (false);
	if (input[i] == '"' && ft_is_space(input[i + 1]) && *flag == 2)
		return (false);
	if (ft_is_space(input[i + 1]) && *flag)
		return (true);
	if (ft_is_space(input[i + 1]) && input[i] != '"' && input[i] != '\'')
		return (false);
	if (input[i + 1] == '>' && *flag && (input[i] == '"' || input[i] == '\''))
		return (false);
	if (input[i + 1] == '<' && *flag && (input[i] == '"' || input[i] == '\''))
		return (false);
	if (input[i + 1] == '|' && *flag && (input[i] == '"' || input[i] == '\''))
		return (false);
	if (input[i + 1] == '|' && !(*flag) && input[i] != '"' && input[i] != '\'')
		return (false);
	if (input[i + 1] == '<' && !(*flag) && input[i] != '"' && input[i] != '\'')
		return (false);
	if (input[i + 1] == '>' && !(*flag) && input[i] != '"' && input[i] != '\'')
		return (false);
	return (true);
}

static int	iterate_word(int *i, char *input)
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
