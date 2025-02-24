/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 14:37:12 by adeters          ###   ########.fr       */
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

void	remove_alias(t_data *data, char *key)
{
	t_env_lst	*tmp;
	t_env_lst	*to_del;

	tmp = data->alias_lst;
	if (!tmp->next)
	{
		ft_env_lstdelone(tmp);
		tmp = NULL;
	}
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(key, tmp->next->filed))
		{
			to_del = tmp->next;
			tmp->next = tmp->next->next;
			ft_env_lstdelone(to_del);
		}
		tmp = tmp->next;
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
			remove_alias(data, command[2]);
			add_aliases_to_file(data);
		}
		else
		{
			entry = delimiter_add_nl(command[1]);
			if (!entry)
				rage_quit(data, ERR_MALLOC, true);
			alias_to_node(data, entry);
			add_aliases_to_file(data);
			free (entry);
		}
	}
}
