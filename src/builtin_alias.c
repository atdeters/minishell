/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/03/09 02:18:43 by andreas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_env_list_nodes(t_env_lst *lst)
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
	char *tmp_filed;
	char *tmp_value;

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
	int			j;
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
		j = 0;
		while(cur && cur->next && j < len - i)
		{
			if (ft_strcmp(cur->filed, cur->next->filed) > 0)
				swap_env_nodes(cur, cur->next);
			cur = cur->next;
			j++;
		}
		i++;
	}
}

int	set_alias(t_data *data, char **command)
{
	char	*entry;

	if (!count_char(command[1], '='))
	{
		print_usage(data, ALIAS_HELP_FILE_PATH);
		return (setnret(data, ERR_ALIAS_USAGE));
	}
	if (check_entry(data, command[1]))
		return (data->error);
	entry = delimiter_add_nl(command[1]);
	if (!entry)
		rage_quit(data, ERR_MALLOC, true, NULL);
	alias_to_node(data, entry);
	// sort_env_list(&data->alias_lst);
	add_aliases_to_file(data);
	free (entry);
	return (0);
}

bool	has_flag_rm_alias(char **command)
{
	if (count_opts(command) != 3)
		return (false);
	if (!ft_strcmp(command[1], "-r"))
		return (true);
	if (!ft_strcmp(command[1], "--remove"))
		return (true);
	return (false);
}

bool	has_flag_help_alias(char **command)
{
	if (count_opts(command) != 2)
		return (false);
	if (!ft_strcmp(command[1], "--help"))
		return (true);
	if (!ft_strcmp(command[1], "-h"))
		return (true);
	return (false);
}

bool	is_nc_alias(char **command)
{
	if (count_opts(command) == 1)
		return (true);
	if (has_flag_rm_alias(command))
		return (true);
	if (count_opts(command) == 2 && count_char(command[1], '='))
		return (true);
	return (false);
}

// Feature: Sort the list
int	ft_alias(t_data *data, char **command)
{
	t_env_lst	*tmp;

	tmp = data->alias_lst;
	sort_env_list(&data->alias_lst);
	if (!command[1])
		print_aliases(tmp);
	else
	{
		if (has_flag_rm_alias(command))
		{
			remove_alias(&data->alias_lst, command[2]);
			add_aliases_to_file(data);
		}
		else if (has_flag_help_alias(command))
			return (print_usage(data, ALIAS_HELP_FILE_PATH), 0);
		else if (count_opts(command) == 2)
			return (set_alias(data, command));
		else
			return (print_usage(data, ALIAS_HELP_FILE_PATH), ERR_ALIAS_USAGE);
	}
	return (0);
}
