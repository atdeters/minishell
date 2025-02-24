/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 14:22:30 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use vovas functions to parse the .vash_alias file and create a list
// make it a builtin function that can show the list and add entry just like
// the export function

void	add_alias_to_file(t_data *data, char *entry)
{
	int	fd;

	fd = open(data->alias_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	write(fd, entry, ft_strlen(entry));
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
	while (lst)
	{
		ft_printf("%s=%s", lst->filed, lst->value);
		lst = lst->next;
	}
}

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
			remove_alias(data, command[2]);
		else
		{
			entry = delimiter_add_nl(command[1]);
			if (!entry)
				rage_quit(data, ERR_MALLOC, true);
			alias_to_node(data, entry);
			add_alias_to_file(data, entry);
			free (entry);
		}
	}
}
