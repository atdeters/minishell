/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_alias_single(t_data *data, char **command)
{
	t_env_lst	*tmp;

	tmp = data->alias_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->filed, command[1]))
		{
			printf("%s\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	p_use_alias();
	return (setnret(data, ERR_BUILTIN_USAGE));
}

int	set_alias(t_data *data, char **command)
{
	char	*entry;

	if (!count_char(command[1], '='))
		return (p_alias_single(data, command));
	if (check_entry(data, command[1]))
		return (data->error);
	entry = ft_strdup(command[1]);
	alias_to_node(data, entry);
	sort_env_list(&data->alias_lst);
	add_aliases_to_file(data);
	free (entry);
	return (0);
}

bool	is_nc_alias(char **command)
{
	if (count_opts(command) != 1)
		return (true);
	if (has_flag_rm_alias(command))
		return (true);
	if (count_opts(command) == 2 && count_char(command[1], '='))
		return (true);
	return (false);
}

int	p_err_alias_inv_rm(char *command)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd("alias: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": entry does not exist\n", 2);
	return (ERR_ALIAS_INV_RM);
}

int	ft_alias(t_data *data, char **command)
{
	t_env_lst	*tmp;

	tmp = data->alias_lst;
	if (!command[1])
		print_env_lst(tmp, false);
	else
	{
		if (has_flag_rm_alias(command))
		{
			if (is_unique_key(data->alias_lst, command[2]))
				return (p_err_alias_inv_rm(command[2]));
			remove_env_node(&data->alias_lst, command[2]);
			add_aliases_to_file(data);
		}
		else if (count_opts(command) == 2)
			return (set_alias(data, command));
		else
			return (p_use_alias(), ERR_BUILTIN_USAGE);
	}
	return (0);
}
