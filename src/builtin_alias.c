/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 12:03:44 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use vovas functions to parse the .vash_alias file and create a list
// make it a builtin function that can show the list and add entry just like
// the export function

static void	error_exit_env(char *f, char *v, t_env_lst *lst, int exit_code)
{
	if (f)
		free(f);
	if (v)
		free(v);
	if (lst)
		ft_env_lstclear(&lst);
	exit(exit_code);
}

static void	transfer_alias_into_node(char *str, t_data *data, int i)
{
	char		*field;
	char		*value;
	t_env_lst	*node;

	field = ft_substr(str, 0, i);
	if (!field)
		error_exit_env(NULL, NULL, data->alias_lst, 1);
	value = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!value)
		error_exit_env(field, NULL, data->alias_lst, 1);
	node = ft_env_lstnew(field, value);
	if (!node)
		error_exit_env(field, value, data->alias_lst, 1);
	if (!data->alias_lst)
		data->alias_lst = node;
	else
		ft_env_lstadd_back(&data->alias_lst, node);
}

void	alias_to_node(t_data *data, char *entry)
{
	int	i;

	i = 0;
	while (entry[i])
	{
		if (entry[i] == '=')
		{
			transfer_alias_into_node(entry, data, i);
			break ;
		}
		i++;
	}
}

int	alias_file_to_lst(t_data *data)
{
	int		fd;
	char	*entry;

	fd = open(".vash_alias", O_RDONLY);
	entry = get_next_line(fd);
	if (!entry)
		return (close(fd), 1);
	while (entry)
	{
		alias_to_node(data, entry);
		free (entry);
		entry = get_next_line(fd);
	}
	close (fd);
	return (0);
}