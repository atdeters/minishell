/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:31:37 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 20:05:20 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_cd(t_data *data, char **command)
{
	if (!command[1] && chdir(data->home_path) == -1)
		return (1);
	// Actually need to replace ~ with home adress for relative path
	if (!ft_strcmp(command[1], "~") && chdir(data->home_path) == -1)
		return (1);
	else if (!ft_strcmp(command[1], "~"))
		return (0);
	if (command[1] && chdir(command[1]) == -1)
		return (1);
	return (0);
}
