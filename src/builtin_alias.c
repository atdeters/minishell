/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 18:00:28 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Feature: Sort the list
int	ft_alias(t_data *data, char **command)
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
				return (data->error);
			entry = delimiter_add_nl(command[1]);
			if (!entry)
				rage_quit(data, ERR_MALLOC, true, NULL);
			alias_to_node(data, entry);
			add_aliases_to_file(data);
			free (entry);
		}
	}
	return (0);
}
