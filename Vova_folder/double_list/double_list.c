/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:22:39 by vsenniko          #+#    #+#             */
/*   Updated: 2025/01/27 17:20:22 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_dlist	*ft_dlstnew(char *content)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*lst = new;
		return ;
	}
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*current;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = ft_dlstlast(*lst);
	current->next = new;
	new->prev = current;
}

int	ft_dlstsize(t_dlist *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
