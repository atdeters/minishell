/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_helpers3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:26:10 by adeters           #+#    #+#             */
/*   Updated: 2025/02/25 15:29:36 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Also needs to return true in bonus for the && or || or ;
bool	needs_expand(char *current, t_token *tmp)
{
	if (!tmp->prev && ft_strcmp(current, tmp->value))
		return (true);
	else if (tmp->prev && tmp->prev->type == PIPE && ft_strcmp(current,
			tmp->value))
		return (true);
	return (false);
}

int	expand_alias(t_data *data, t_token **lst)
{
	t_token	*tmp;
	t_token	*last;
	t_token	*old;
	t_token	*expanded;
	char	*current;

	tmp = *lst;
	expanded = NULL;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			current = get_value_from_lst(data->alias_lst, tmp->value);
			if (!current)
				rage_quit(data, ERR_MALLOC, true);
			if (needs_expand(current, tmp))
			{
				current = rid_of_nl(current);
				if (!lexing(current, &expanded, &data->error))
				{
					free(current);
					rage_quit(data, ERR_LEXING, true);
				}
				last = ft_token_lstlast(expanded);
				last->next = tmp->next;
				old = tmp;
				if (tmp->prev)
					tmp->prev->next = expanded;
				else
					data->token_lst = expanded;
				ft_token_lstdelone(old);
				tmp = last;
			}
			free(current);
		}
		tmp = tmp->next;
	}
	return (0);
}
