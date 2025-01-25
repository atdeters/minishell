/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:25:51 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:30 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (last != 0)
		last->next = new;
	else
		*lst = new;
}
/*
#include <stdio.h>

int	main(void)
{
	char *text = "Hello";
	char *text1 = " World!";
	char *text2 = "Blyat";
	t_list *node = ft_lstnew(text);
	t_list *node1 = ft_lstnew(text1);
	t_list *node2 = ft_lstnew(text2);
	ft_lstadd_front(&node, node1);
	ft_lstadd_front(&node1, node2);
	char *text3 = "Xicht!";
	t_list *node3 = ft_lstnew(text3);
	ft_lstadd_back(&node2, node3);
	t_list *last = ft_lstlast(node2);
	printf("%p\n", last);
	printf("%p\n", node3);
} */