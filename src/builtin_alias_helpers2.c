/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_helpers2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:24:14 by adeters           #+#    #+#             */
/*   Updated: 2025/03/24 18:20:02 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_node(t_env_lst **lst, char *key)
{
	t_env_lst	*head;
	t_env_lst	*tmp;
	t_env_lst	*current;

	if (!lst | !*lst)
		return ;
	head = *lst;
	if (!ft_strcmp(key, (*lst)->filed))
	{
		*lst = head->next;
		ft_env_lstdelone(head);
		return ;
	}
	current = head;
	while (current && current->next)
	{
		if (!ft_strcmp(key, current->next->filed))
		{
			tmp = current->next->next;
			ft_env_lstdelone(current->next);
			current->next = tmp;
			return ;
		}
		current = current->next;
	}
}

char	*extract_alias_key(t_data *data, char *entry)
{
	int		eq_ind;
	char	*dupe;

	if (ft_strchr(entry, '='))
	{
		eq_ind = ft_strchr(entry, '=') - entry;
		dupe = ft_strdup(entry);
		if (!dupe)
			rage_quit(data, ERR_MALLOC, true, NULL);
		dupe[eq_ind] = '\0';
	}
	else
	{
		dupe = ft_strdup(entry);
		if (!dupe)
			rage_quit(data, ERR_MALLOC, true, NULL);
	}
	return (dupe);
}

void	extract_and_remove(t_data *data, char *entry)
{
	char	*dupe;

	dupe = extract_alias_key(data, entry);
	remove_env_node(&data->alias_lst, dupe);
	free(dupe);
}

void	p_alias_dup(t_data *data, char *entry)
{
	char	*dupe;

	dupe = extract_alias_key(data, entry);
	ft_putstr_fd("\"", 2);
	ft_putstr_fd(dupe, 2);
	ft_putstr_fd("\"", 2);
	ft_putstr_fd(" is not a unique entry.\n", 2);
	ft_putstr_fd("Do you want to overwrite it? [Y/n] ", 2);
	free (dupe);
}

int	check_entry(t_data *data, char *entry)
{
	if (!is_valid_entry_form(entry))
	{
		printf("Not a valid entry for alias\n");
		return (setnret(data, ERR_INVALID_ENTRY));
	}
	if (!is_unique_key(data->alias_lst, entry))
		return (extract_and_remove(data, entry), 0);
	return (0);
}

//* Version that asks the user for permission to overwrite
// int	check_entry(t_data *data, char *entry)
// {
// 	if (!is_valid_entry_form(entry))
// 	{
// 		printf("Not a valid entry for alias\n");
// 		return (setnret(data, ERR_INVALID_ENTRY));
// 	}
// 	if (!is_unique_key(data->alias_lst, entry))
// 	{
// 		p_alias_dup(data, entry);
// 		if (user_agrees(data))
// 			return (extract_and_remove(data, entry), 0);
// 		else
// 			return (setnret(data, ERR_DUP_ENTRY));
// 	}
// 	return (0);
// }
