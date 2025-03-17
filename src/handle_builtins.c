/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:16:54 by adeters           #+#    #+#             */
/*   Updated: 2025/03/17 17:47:56 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (true);
	if (!ft_strcmp(name, "cd"))
		return (true);
	if (!ft_strcmp(name, "pwd"))
		return (true);
	if (!ft_strcmp(name, "export"))
		return (true);
	if (!ft_strcmp(name, "unset"))
		return (true);
	if (!ft_strcmp(name, "env"))
		return (true);
	if (!ft_strcmp(name, "exit"))
		return (true);
	if (!ft_strcmp(name, "alias"))
		return (true);
	return (false);
}

bool	handle_nc_builtin(t_data *data, char **command)
{
	if (!ft_strcmp(command[0], "cd"))
		return (data->exit_status = ft_cd(data, command), true);
	else if (!ft_strcmp(command[0], "exit"))
		return (data->exit_status = ft_exit(data, command), true);
	else if (!ft_strcmp(command[0], "alias") && is_nc_alias(command))
		return (data->exit_status = ft_alias(data, command), true);
	else if (!ft_strcmp(command[0], "export") && command[1])
		return (data->exit_status = ft_export(data, command), true);
	else if (!ft_strcmp(command[0], "unset"))
		return (data->exit_status = ft_unset(data, command), true);
	return (false);
}

bool	handle_builtin(t_data *data, char **command)
{
	if (!ft_strcmp(command[0], "echo"))
		return (ft_echo(command), true);
	else if (!ft_strcmp(command[0], "pwd"))
		return (ft_pwd(data, command), true);
	// nc_builtins dont have to be done here
	if (!ft_strcmp(command[0], "cd"))
		return (true);
	else if (!ft_strcmp(command[0], "exit"))
		return (true);
	else if (!ft_strcmp(command[0], "alias") && is_nc_alias(command))
		return (true);
	else if (!ft_strcmp(command[0], "alias"))
		return (data->exit_status = ft_alias(data, command), true);
	else if (!ft_strcmp(command[0], "export") && command[1])
		return (true);
	else if (!ft_strcmp(command[0], "export"))
		return (ft_export(data, command), true);
	else if (!ft_strcmp(command[0], "unset"))
		return (true);
	else if (!ft_strcmp(command[0], "env"))
		return (ft_env(data), true);
	else
		return (false);
}
