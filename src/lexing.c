/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:11 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/20 17:56:07 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static int	process_token(char *input, t_token **current, int *i)
{
	if (input[*i] == '$' || input[*i] == '|' || input[*i] == '<'
		|| input[*i] == '>')
	{
		if (!handle_special_char(input, current, i))
			return (0);
	}
	else if (input[*i] == '\'')
	{
		if (!handle_single_quote(i, input, current))
			return (0);
	}
	else if (input[*i] == '"')
	{
		if (!handle_double_quotes(i, input, current))
			return (0);
	}
	else
	{
		if (!handle_word(i, input, current))
			return (0);
	}
	return (1);
}

int	lexing(char *input, t_token **list, int *err_code)
{
	t_token	*current;
	int		i;

	i = 0;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (!input[i])
		return (1);
	if (input[i] == '|')
		return (*err_code = 130, 0);
	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			return (1);
		if (!process_token(input, &current, &i))
			return (*err_code = 130, 0);
		ft_token_lstadd_back(list, current);
		if (input[i])
			i++;
	}
	return (1);
}
