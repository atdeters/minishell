/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:23:03 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:36 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;
	t_list	*tmp;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(*lst);
	next_node = *lst;
	*lst = 0;
	while (i < size)
	{
		del(next_node->content);
		tmp = next_node->next;
		free(next_node);
		next_node = tmp;
		i++;
	}
}
/* 
void	del(void *content)
{ 
	free(content);
}

#include <stdio.h>

int	main(void)
{
	char *text = ft_strdup("Hello");
	char *text1 = ft_strdup(" World!");
	char *text2 = ft_strdup("Blyat");
	t_list *node = ft_lstnew(text);
	t_list *node1 = ft_lstnew(text1);
	t_list *node2 = ft_lstnew(text2);
	ft_lstadd_front(&node, node1);
	ft_lstadd_front(&node1, node2);
	ft_lstclear(&node2, del);
} */