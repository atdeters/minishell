/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:25:05 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:52 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*follow;

	counter = 1;
	if (lst == 0)
		return (0);
	follow = lst->next;
	while (follow != 0)
	{
		counter++;
		follow = follow->next;
	}
	return (counter);
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
	int size = ft_lstsize(node2);
	printf("%i\n", size);
} */