/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:16:55 by adeters           #+#    #+#             */
/*   Updated: 2025/03/28 19:20:04 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes a single token from the input string
 * @param input The input string to process
 * @param current Pointer to store the created token
 * @param i Current position in the input string
 * @param data Shell data structure containing error handling info
 * @return 1 on success, 0 on failure
 * 
 * Used to be a part of process_token between if and else:
 * 
 * 		else if (input[*i] == '\'')
 * 		{
 * 		if (!handle_single_quote(i, input, current))
 * 			return (0);
 * 		}
 * 		else if (input[*i] == '"')
 * 		{
 * 			if (!handle_double_quotes(i, input, current))
 * 				return (0);
 * 		}
 */
static int	process_token(char *input, t_token **current, int *i, t_data *data)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		if (!handle_special_char(input, current, i, data))
		{
			if (data->error == ERR_MALLOC)
				rage_quit(data, data->error, true, NULL);
			return (0);
		}
	}
	else
	{
		if (!handle_word(i, input, current, data))
		{
			if (data->error == ERR_MALLOC)
				rage_quit(data, data->error, true, NULL);
			return (0);
		}
	}
	return (1);
}

int	lexing(char *input, t_token **list, t_data *data)
{
	t_token	*current;
	int		i;

	i = 0;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (!input[i])
		return (1);
	if (input[i] == '|')
		return (data->error = ERR_PARS, 0);
	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			return (1);
		if (!process_token(input, &current, &i, data))
			return (data->error = ERR_PARS, 0);
		ft_token_lstadd_back(list, current);
		if (input[i])
			i++;
	}
	return (1);
}
