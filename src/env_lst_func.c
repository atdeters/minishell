/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:17:55 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/21 16:00:19 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*ft_env_lstnew(char *f, char *v)
{
	t_env_lst	*node;

	node = malloc(sizeof(t_env_lst));
	if (node == NULL)
		return (NULL);
	node->filed = f;
	node->value = v;
	node->next = NULL;
	return (node);
}

t_env_lst	*ft_env_lstlast(t_env_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_env_lstadd_back(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst	*current;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = ft_env_lstlast(*lst);
	current->next = new;
}

void	ft_env_lstdelone(t_env_lst *lst)
{
	if (lst == NULL)
		return ;
	if (lst->filed)
		free(lst->filed);
	if (lst->value)
		free(lst->value);
	free(lst);
}

void	ft_env_lstclear(t_env_lst **lst)
{
	t_env_lst	*current;
	t_env_lst	*tmp;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_env_lstdelone(tmp);
	}
	*lst = NULL;
}
