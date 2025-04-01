/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:23:35 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/01 17:07:15 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_p_and_c(int p_type, char *p_value, int c_type, char *c_value)
{
	if (p_type == DELIMITER && p_value && (p_value[0] == '>'
			|| p_value[0] == '<' || p_value[0] == '|'))
		return (1);
	if (c_type == DELIMITER && c_value && (c_value[0] == '>'
			|| c_value[0] == '<' || c_value[0] == '|'))
		return (1);
	if (p_type == PIPE && c_type == PIPE)
		return (1);
	if ((p_type == REDIR_IN && c_type == REDIR_OUT) || (p_type == REDIR_OUT
			&& c_type == REDIR_IN))
		return (1);
	if (p_type == REDIR_APPEND && ((c_type == REDIR_IN || c_type == REDIR_OUT
				|| c_type == DELIMITER || c_type == PIPE)))
		return (1);
	return (0);
}

static int	check_single_case(t_token *prev)
{
	if (prev->type == DELIMITER && prev->value && (prev->value[0] == '>'
			|| prev->value[0] == '<' || prev->value[0] == '|'
			|| prev->value[0] == '\0'))
		return (1);
	return (0);
}

static int	problem_with_redir(t_token *lst)
{
	t_token	*prev;
	t_token	*curr;

	prev = lst;
	curr = lst->next;
	if (!curr && check_single_case(prev))
		return (1);
	while (curr)
	{
		if (check_p_and_c(prev->type, prev->value, curr->type, curr->value))
			return (1);
		if ((curr->type == PIPE || curr->type == REDIR_APPEND
				|| curr->type == REDIR_IN || curr->type == REDIR_OUT)
			&& curr->next == NULL)
			return (1);
		if ((prev->type == PIPE || prev->type == REDIR_APPEND
				|| prev->type == REDIR_IN || prev->type == REDIR_OUT)
			&& curr == NULL)
			return (1);
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	check_patern(t_data *data)
{
	if (problem_with_redir(data->token_lst))
		return (0);
	return (1);
}
