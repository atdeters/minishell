/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:19:20 by adeters           #+#    #+#             */
/*   Updated: 2024/11/15 19:50:47 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	*ft_lstincrease(t_list *old, int size, void (*del)(void *));
static void		ft_free_cont(t_list *dup, int size, void (*del)(void *));
static t_list	*ft_dupfail(t_list *dup, int size, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		size;
	int		i;
	t_list	*dup;
	t_list	*ptr;

	i = 0;
	size = ft_lstsize(lst) - 1;
	dup = (t_list *)malloc(sizeof(t_list));
	if (dup == 0)
		return (0);
	dup = ft_lstincrease(dup, size, del);
	if (dup == 0)
		return (0);
	ptr = dup;
	while (i < (size + 1))
	{
		dup->content = ft_strdup(f(lst->content));
		if (dup->content == 0)
			return (ft_dupfail(dup, i, del));
		dup = dup->next;
		lst = lst->next;
		i++;
	}
	return (ptr);
}

static t_list	*ft_lstincrease(t_list *old, int size, void (*del)(void *))
{
	t_list	*node;

	if (size != 0)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (node == 0)
		{
			ft_lstclear(&old, del);
			return (0);
		}
		node->content = 0;
		ft_lstadd_front(&old, node);
		return (ft_lstincrease(node, size - 1, del));
	}
	return (old);
}

static void	ft_free_cont(t_list *dup, int size, void (*del)(void *))
{
	int	i;

	i = 0;
	while (i < size && dup != 0)
	{
		del(dup->content);
		dup = dup->next;
		i++;
	}
}

static t_list	*ft_dupfail(t_list *dup, int size, void (*del)(void *))
{
	ft_free_cont(dup, size, del);
	ft_lstclear(&dup, del);
	return (0);
}
/* 
static void	del(void *content)
{
	free(content);
}

void	*f(void *content)
{
	char	*ptr;

	ptr = (char *)content;
	if (ptr != 0)
		ptr[0] = ft_tolower(ptr[0]);
	return (ptr);
}

#include <stdio.h>

int	main(void)
{
	char *text = ft_strdup("Hello");
	char *text1 = ft_strdup("World");
	char *text2 = ft_strdup("Blyat");
	t_list *node = ft_lstnew(text);
	t_list *node1 = ft_lstnew(text1);
	t_list *node2 = ft_lstnew(text2);
	ft_lstadd_front(&node, node1);
	ft_lstadd_front(&node1, node2);
	t_list *dup = ft_lstmap(node2, f, del);
	printf("%s\n", (char *)node2->content);
	printf("%s\n", (char *)dup->content);
	ft_lstclear(&node2, del);
	ft_lstclear(&dup, del);
} */