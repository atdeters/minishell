/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 17:20:47 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use vovas functions to parse the .vash_alias file and create a list
// make it a builtin function that can show the list and add entry just like
// the export function

void	add_aliases_to_file(t_data *data)
{
	int			fd;
	t_env_lst	*tmp;

	fd = open(data->alias_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	tmp = data->alias_lst;
	if (!tmp)
	{
		close (fd);
		return ;
	}
	while (tmp)
	{
		write(fd, tmp->filed, ft_strlen(tmp->filed));
		write(fd, "=", 1);
		write(fd, tmp->value, ft_strlen(tmp->value));
		tmp = tmp->next;
	}
	write(fd, "\n", 1);
	close (fd);
}

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

static void	print_aliases(t_env_lst *lst)
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

/**
 * This function assumes that the entry has exactly one "="
 * It segfaults if used without one!!
 */
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
		return (false); // Add error message;
	key[eq_ind] = '\0';
	check = get_value_from_lst(lst, key);
	if (!ft_strcmp(check, key))
		return (free(key), true);
	return (free(key), false);
}

bool check_entry(t_data *data, char *entry)
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

// Feature: Sort the list
// Feature: Throw arrow when key already exists and don't add it in
void	ft_alias(t_data *data, char **command)
{
	t_env_lst	*tmp;
	char		*entry;

	tmp = data->alias_lst;
	if (!command[1])
		print_aliases(tmp);
	else
	{
		if (command[2] && !strcmp(command[1], "rm"))
		{
			remove_alias(&data->alias_lst, command[2]);
			add_aliases_to_file(data);
		} 
		else
		{
			if (!check_entry(data, command[1]))
				return ;
			entry = delimiter_add_nl(command[1]);
			if (!entry)
				rage_quit(data, ERR_MALLOC, true);
			alias_to_node(data, entry);
			add_aliases_to_file(data);
			free (entry);
		}
	}
}
