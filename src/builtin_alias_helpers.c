/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:36:59 by adeters           #+#    #+#             */
/*   Updated: 2025/03/17 19:04:49 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	load_alias_lst(t_data *data, char *path)
{
	int		fd;
	char	*entry;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	entry = get_next_line(fd);
	if (!entry)
		return (close(fd), 1);
	while (entry)
	{
		entry = rid_of_nl(entry);
		if (ft_strchr(entry, '='))
			alias_to_node(data, entry);
		free (entry);
		entry = get_next_line(fd);
	}
	sort_env_list(&data->alias_lst);
	close (fd);
	return (0);
}

// Add error messages
void	add_aliases_to_file(t_data *data)
{
	int			fd;
	t_env_lst	*tmp;

	fd = open(data->alias_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	tmp = data->alias_lst;
	if (!tmp)
		return ((void)close (fd));
	while (tmp)
	{
		write(fd, tmp->filed, ft_strlen(tmp->filed));
		write(fd, "=", 1);
		write(fd, tmp->value, ft_strlen(tmp->value));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	write(fd, "\n", 1);
	close (fd);
}
