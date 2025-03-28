/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:24:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/28 17:40:34 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (true);
	if (input[i + 1] == '<' && !(*flag))
		return (true);
	if (input[i + 1] == '>' && !(*flag))
		return (true);
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
