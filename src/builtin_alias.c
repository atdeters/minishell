/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 12:47:06 by adeters          ###   ########.fr       */
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

void	ft_alias(t_data *data, char **command)
{
	t_env_lst	*tmp;
	char		*entry;

	// Add functionality to remove aliases
	tmp = data->alias_lst;
	// Loop through it and give errors for everything
	// That is bullshit like command[1] with no or more than 1 '='
	// Or more than 1 option after the "alias"
	if (!command[1])
	{
		while (tmp)
		{
			ft_printf("%s=", tmp->filed);
			ft_printf("%s", tmp->value);
			tmp = tmp->next;
		}
	}
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
