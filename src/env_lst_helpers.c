/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:24:17 by andreas           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_list_nodes(t_env_lst *lst)
{
	t_env_lst	*tmp;
	int			counter;

	tmp = lst;
	counter = 0;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

void	swap_env_nodes(t_env_lst *node1, t_env_lst *node2)
{
	char	*tmp_filed;
	char	*tmp_value;

	tmp_filed = node1->filed;
	tmp_value = node1->value;
	node1->filed = node2->filed;
	node1->value = node2->value;
	node2->filed = tmp_filed;
	node2->value = tmp_value;
}

void	sort_env_list(t_env_lst **lst)
{
	int			len;
	int			i;
	t_env_lst	*cur;

	len = count_env_list_nodes(*lst);
	if (len <= 1)
		return ;
	if (len == 2 && ft_strcmp((*lst)->filed, (*lst)->next->filed) > 0)
		return (swap_env_nodes(*lst, (*lst)->next));
	else if (len == 2)
		return ;
	i = 0;
	while (i < len)
	{
		cur = *lst;
		while (cur && cur->next)
		{
			if (ft_strcmp(cur->filed, cur->next->filed) > 0)
				swap_env_nodes(cur, cur->next);
			cur = cur->next;
		}
		i++;
	}
}
