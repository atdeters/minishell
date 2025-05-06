/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:32:48 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Already exists + no redefinition -> nothing happens
// Already exists + redefinition -> overwriting
// Doesn't exit + no definition -> will be implemented without a value

bool	is_valid_ident(char *entry)
{
	int	i;

	i = 1;
	if (!ft_isalpha(entry[0]) && entry[0] != '_')
		return (false);
	while (entry[i])
	{
		if (entry[i] == '=')
			return (true);
		if (!ft_isalnum(entry[i]) && entry[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	add_env(t_data *data, char *entry)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!is_valid_ident(entry))
		return (p_err_arg(ERR_VALID_IDENT, entry));
	while (entry[j])
	{
		if (entry[j] == '=')
		{
			tmp = ft_substr(entry, 0, j);
			if (!tmp)
				rage_quit(data, ERR_MALLOC, true, NULL);
			remove_env_node(&data->env_lst, tmp);
			free(tmp);
			transfer_into_node(entry, data, j);
			break ;
		}
		j++;
	}
	if (!ft_strchr(entry, '=') && is_unique_key(data->env_lst, entry))
		transfer_into_node(entry, data, j);
	return (0);
}

int	export_envs(t_data *data, char **command)
{
	int		var_count;
	int		i;
	bool	flag;

	flag = false;
	var_count = count_opts(command);
	i = 1;
	while (i < var_count)
	{
		while (command[i])
		{
			if (add_env(data, command[i]))
				flag = true;
			i++;
		}
	}
	if (flag)
		return (ERR_VALID_IDENT);
	else
		return (0);
}

int	ft_export(t_data *data, char **command)
{
	t_env_lst	*export_lst;

	export_lst = data->env_lst;
	if (!command[1])
	{
		sort_env_list(&export_lst);
		print_env_lst(export_lst, true);
		return (0);
	}
	else
		return (export_envs(data, command));
}
