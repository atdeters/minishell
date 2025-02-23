/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:11 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/23 20:47:00 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "minishell.h"

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



// int	lexing(char *input, t_token **list, int *err_code)
// {
// 	t_token	*current;
// 	int		i;

// 	i = 0;
// 	while (input[i] && ft_is_space(input[i]))
// 		i++;
// 	if (!input[i])
// 		return (1);
// 	if (input[i] == '|')
// 		return (*err_code = 130, 0);
// 	while (input[i])
// 	{
// 		while (input[i] && ft_is_space(input[i]))
// 			i++;
// 		if (!input[i])
// 			return (1);
// 		if (!process_token(input, &current, &i))
// 			return (*err_code = 130, 0);
// 		ft_token_lstadd_back(list, current);
// 		if (input[i])
// 			i++;
// 	}
// 	return (1);
// }


int	lexing(t_data *data)
{
	t_token	*current;
	int		i;

	i = 0;
	while (data->input[i] && ft_is_space(data->input[i]))
		i++;
	if (!data->input[i])
		return (0);
	if (data->input[i] == '|')
		return (setnret(data, ERR_PARS));
	while (data->input[i])
	{
		while (data->input[i] && ft_is_space(data->input[i]))
			i++;
		if (!data->input[i])
			return (0);
		if (!process_token(data->input, &current, &i))
			return (setnret(data, ERR_PARS));
		ft_token_lstadd_back(&data->token_lst, current);
		if (data->input[i])
			i++;
	}
	return (0);
}

