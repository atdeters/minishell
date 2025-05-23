/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_helpers3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:26:10 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	replace_alias(t_data *data, char *current, t_token **tmp)
{
	t_token	*expanded;
	t_token	*last;
	t_token	*old;

	current = rid_of_nl(current);
	expanded = NULL;
	if (!lexing(current, &expanded, data))
	{
		free(current);
		rage_quit(data, ERR_LEXING, true, NULL);
	}
	last = ft_token_lstlast(expanded);
	last->next = (*tmp)->next;
	expanded->prev = (*tmp)->prev;
	if ((*tmp)->next)
		(*tmp)->next->prev = last;
	old = *tmp;
	if ((*tmp)->prev)
		(*tmp)->prev->next = expanded;
	else
		data->token_lst = expanded;
	ft_token_lstdelone(old);
	*tmp = last;
}

int	expand_alias(t_data *data, t_token **lst)
{
	t_token	*tmp;
	char	*current;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			current = get_value_from_lst(data->alias_lst, tmp->value);
			if (!current)
				rage_quit(data, ERR_MALLOC, true, NULL);
			if (needs_expand(current, tmp))
				replace_alias(data, current, &tmp);
			free(current);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	print_env_lst(t_env_lst *lst, bool is_export)
{
	if (!lst)
		printf("alias list currently emtpy\n");
	while (lst)
	{
		if (is_export)
		{
			ft_printf("declare -x ");
			ft_printf("%s=\"%s\"\n", lst->filed, lst->value);
		}
		else
			ft_printf("%s=%s\n", lst->filed, lst->value);
		lst = lst->next;
	}
}
