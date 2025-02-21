/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:39:01 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/21 15:41:49 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pars_data(t_pars_data *pars_data, t_data *data, t_token **tokens)
{
	pars_data->env_lst = &data->env_lst;
	pars_data->token_lst = tokens;
	pars_data->cmd_amount = pipe_counter(tokens) + 1;
	data->pipes_amount = pipe_counter(tokens);
	pars_data->parsed_amount = 0;
}

int	check_for_count(t_token *token)
{
	if ((token->type == WORD || token->type == DOUBLE_QOUTE
			|| token->type == DOLAR_SIGN || token->type == SINGLE_QOUTE)
		&& (!token->prev || (token->prev && (token->prev->type != REDIR_APPEND
					&& token->prev->type != REDIR_OUT
					&& token->prev->type != REDIR_IN
					&& token->prev->type != DELIMITER))))
		return (1);
	return (0);
}

int	check_for_putting_words(t_token *token)
{
	if ((token->type == WORD || token->type == DOUBLE_QOUTE
			|| token->type == SINGLE_QOUTE) && (!token->prev || (token->prev
				&& (token->prev->type != REDIR_APPEND
					&& token->prev->type != REDIR_OUT
					&& token->prev->type != REDIR_IN
					&& token->prev->type != DELIMITER))))
		return (1);
	return (0);
}

int	check_for_putting_dollar(t_token *token)
{
	if (token->type == DOLAR_SIGN && (!token->prev || (token->prev
				&& (token->prev->type != REDIR_APPEND
					&& token->prev->type != REDIR_OUT
					&& token->prev->type != REDIR_IN
					&& token->prev->type != DELIMITER))))
		return (1);
	return (0);
}

char	*return_from_env(t_pars_data pars_data, char *field)
{
	t_env_lst	*tmp;
	char		*res;

	res = NULL;
	tmp = *pars_data.env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->filed, field, ft_strlen(tmp->filed)) == 0)
		{
			res = ft_strdup(tmp->value);
			if (!res)
				return (NULL);
			return (res);
		}
		tmp = tmp->next;
	}
	res = malloc(sizeof(char));
	res[0] = '\0';
	return (res);
}
