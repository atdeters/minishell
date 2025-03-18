/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:32:48 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 13:49:21 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, char **command)
{
	t_env_lst *export_lst;

	export_lst = data->env_lst;
	if (!command[1])
	{
		sort_env_list(&export_lst);
		print_env_lst(export_lst, true);
	}
	return (0);
}
