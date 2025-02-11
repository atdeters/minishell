/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:53:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/11 18:09:34 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token	*create_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*ft_token_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = ft_token_lstlast(*lst);
	current->next = new;
}

static void	ft_token_lstdelone(t_token *lst)
{
	if (lst == NULL)
		return ;
	if (lst->value)
		free(lst->value);
	free(lst);
}

void	ft_token_lstclear(t_token **lst)
{
	t_token	*current;
	t_token	*tmp;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_token_lstdelone(tmp);
	}
	*lst = NULL;
}
