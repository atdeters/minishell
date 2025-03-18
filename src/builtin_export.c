/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:32:48 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 16:38:24 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Already exists + no redefinition -> nothing happens
// Already exists + redefinition -> overwriting
// Doesn't exit + no definition -> will be implemented without a value

void	export_envs(t_data *data, char **command)
{
	int		var_count;
	int		i;
	int		j;
	char	*tmp;

	var_count = count_opts(command);
	i = 1;
	while (i < var_count)
	{
		while (command[i])
		{
			j = 0;
			while (command[i][j])
			{
				if (command[i][j] == '=')
				{
					tmp = ft_substr(command[i], 0, j);
					if (!tmp)
						rage_quit(data, ERR_MALLOC, true, NULL);
					remove_alias(&data->env_lst, tmp);
					free (tmp);
					transfer_into_node(command[i], data, j);
					break ;
				}
				j++;
			}
			if (!ft_strchr(command[i], '=') && is_unique_key(data->env_lst, command[i]))
				transfer_into_node(command[i], data, j);
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
