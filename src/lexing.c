/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:16:55 by adeters           #+#    #+#             */
/*   Updated: 2025/05/09 16:43:57 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Processes a single token from the input string
 * @param input The input string to process
 * @param current Pointer to store the created token
 * @param i Current position in the input string
 * @param data Shell data structure containing error handling info
 * @return 1 on success, 0 on failure
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

static int	check_replace(t_token **lst)
{
	t_token	*token;
	t_token	*tmp;

	token = *lst;
	while (token)
	{
		if (token->type == DELIMITER && token->next)
		{
			token->value = ft_strdup(token->next->value);
			if (!token->value)
				return (0);
			free(token->next->value);
			tmp = token->next;
			token->next = tmp->next;
			if (token->next)
				token->next->prev = token;
			free(tmp);
		}
		else if (token->type == DELIMITER && !token->next)
			return (0);
		token = token->next;
	}
	return (1);
}

static int	provide_check_and_delim(t_token **lst, t_data *data)
{
	if (!check_replace(lst))
		return (0);
	if (!check_patern(data))
		return (0);
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
	if (!provide_check_and_delim(list, data))
		return (data->error = ERR_PARS, 0);
	return (1);
}
