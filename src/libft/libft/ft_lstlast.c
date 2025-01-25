/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:25:11 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:43 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (lst);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
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
	ft_lstadd_front(&node, node2);
	t_list *last = ft_lstlast(node);
	printf("%p\n", last);
	printf("%p\n", node1);
} */