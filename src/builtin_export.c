/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:32:48 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 16:59:29 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Already exists + no redefinition -> nothing happens
// Already exists + redefinition -> overwriting
// Doesn't exit + no definition -> will be implemented without a value

static void	add_env(t_data *data, char *entry)
{
	int		j;
	char	*tmp;

	j = 0;
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
}

void	export_envs(t_data *data, char **command)
{
	int		var_count;
	int		i;

	var_count = count_opts(command);
	i = 1;
	while (i < var_count)
	{
		while (command[i])
		{
			add_env(data, command[i]);
			i++;
		}
	}
}

int	ft_export(t_data *data, char **command)
{
	t_env_lst	*export_lst;

	export_lst = data->env_lst;
	if (!command[1])
	{
		sort_env_list(&export_lst);
		print_env_lst(export_lst, true);
	}
	else
		export_envs(data, command);
	return (0);
}
