/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:31:08 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:41 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != 0)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void	func(void *content)
{
	char	*ptr;

	ptr = (char *)content;
	if (ptr != 0)
		ptr[0] = ft_tolower(ptr[0]);
}

#include <stdio.h>

	int
	main(void)
{
	char *text = ft_strdup("Hello");
	char *text1 = ft_strdup("World!");
	char *text2 = ft_strdup("Blyat");
	t_list *node = ft_lstnew(text);
	t_list *node1 = ft_lstnew(text1);
	t_list *node2 = ft_lstnew(text2);
	ft_lstadd_front(&node, node1);
	ft_lstadd_front(&node1, node2);
	ft_lstiter(node2, func);
	printf("%s\n", (char *)node->content);
} */