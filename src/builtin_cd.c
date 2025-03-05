/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:31:37 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 16:21:52 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_cd(t_data *data, char **command)
{
	if (!command[1] && chdir(data->home_path) == -1)
		rage_quit(data, ERR_CHDIR, true, NULL);
	// Actually need to replace ~ with home adress for relative path
	if (!ft_strcmp(command[1], "~") && chdir(data->home_path) == -1)
		rage_quit(data, ERR_CHDIR, true, NULL);
	else if (!ft_strcmp(command[1], "~"))
		return (0);
	if (command[1] && chdir(command[1]) == -1)
		rage_quit(data, ERR_CHDIR, true, NULL);
	return (0);
}
