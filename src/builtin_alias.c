/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:45:36 by adeters           #+#    #+#             */
/*   Updated: 2025/03/09 12:48:59 by andreas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	sort_env_list(&data->alias_lst);
	add_aliases_to_file(data);
	free (entry);
	return (0);
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
		print_aliases(tmp);
	else
	{
		if (has_flag_rm_alias(command))
		{
			if (is_unique_key(data->alias_lst, command[2]))
				return (p_err_alias_inv_rm(command[2]));
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
