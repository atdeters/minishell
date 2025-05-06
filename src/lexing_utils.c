/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:53:53 by vsenniko          #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Creates a new token with given type and value
 * @param type Token type (WORD, PIPE, etc.)
 * @param value String value for the token
 * @return Pointer to new token or NULL on failure
 */
t_token	*create_token(int type, char *value)
{
	t_token	*token;

	if (type == WORD && !value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/**
 * @brief Finds the last token in a token list
 * @param lst Head of the token list
 * @return Pointer to last token or NULL if list is empty
 */
t_token	*ft_token_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/**
 * @brief Adds a new token to the end of the token list
 * @param lst Pointer to token list head
 * @param new Token to add
 */
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
	new->prev = current;
}

/**
 * @brief Deletes a single token and frees its memory
 * @param lst Token to delete
 */
void	ft_token_lstdelone(t_token *lst)
{
	if (lst == NULL)
		return ;
	if (lst->value)
		free(lst->value);
	free(lst);
}

/**
 * @brief Clears entire token list and frees all memory
 * @param lst Pointer to token list head
 */
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
