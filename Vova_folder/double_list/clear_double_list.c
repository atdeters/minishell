/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_double_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:30:20 by vsenniko          #+#    #+#             */
/*   Updated: 2025/01/27 17:19:42 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	free(lst);
}

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*current;
	t_dlist	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_dlstdelone(tmp, del);
	}
	*lst = NULL;
}
