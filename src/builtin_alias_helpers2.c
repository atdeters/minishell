/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_helpers2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:24:14 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 17:27:34 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_alias(t_env_lst **lst, char *key)
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

void	print_aliases(t_env_lst *lst)
{
	if (!lst)
		printf("alias list currently emtpy\n");
	while (lst)
	{
		ft_printf("%s=%s", lst->filed, lst->value);
		lst = lst->next;
	}
}

bool	is_valid_entry_form(char *entry)
{
	int	eq_count;
	int	i;

	eq_count = 0;
	i = 0;
	while (entry[i])
	{
		if (entry[i] == '=')
			eq_count++;
		i++;
	}
	if (eq_count != 1)
		return (false);
	return (true);
}

bool	is_unique_key(t_env_lst *lst, char *entry)
{
	char	*key;
	char	*check;
	int		eq_ind;

	if (!lst)
		return (true);
	eq_ind = ft_strchr(entry, '=') - entry;
	key = ft_strdup(entry);
	if (!key)
		return (false);
	key[eq_ind] = '\0';
	check = get_value_from_lst(lst, key);
	if (!ft_strcmp(check, key))
		return (free(key), true);
	return (free(key), false);
}

bool	check_entry(t_data *data, char *entry)
{
	if (!is_valid_entry_form(entry))
	{
		printf("Not a valid entry for alias\n");
		return (false);
	}
	if (!is_unique_key(data->alias_lst, entry))
	{
		ft_printf("\"%s\" is not a unique entry.\n", entry);
		ft_printf("Choose another one or remove this one ");
		ft_printf("by using \"alias rm [key]\"\n");
		return (false);
	}
	return (true);
}
