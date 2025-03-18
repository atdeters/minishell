/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:40:35 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 16:27:31 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char **command)
{
	int	var_count;
	int	i;

	var_count = count_opts(command);
	i = 1;
	if (var_count < 2)
		return (ERR_BUILTIN_USAGE);
	while (i < var_count)
	{
		remove_alias(&data->env_lst, command[i]);
		i++;
	}
	return (0);
}
