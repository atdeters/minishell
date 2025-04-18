/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:16:54 by adeters           #+#    #+#             */
/*   Updated: 2025/04/19 00:04:31 by andreas          ###   ########.fr       */
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
	if (!ft_strcmp(name, "biman"))
		return (true);
	return (false);
}

bool	handle_nc_builtin(t_data *data, char **command)
{
	if (!command[0])
		return (false);
	if (!ft_strcmp(command[0], "cd"))
		return (data->exit_status = ft_cd(data, command), true); // TODO: Make it ragequit here on critical errors 
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
		return (data->exit_status = ft_echo(command), true);
	else if (!ft_strcmp(command[0], "pwd"))
		return (data->exit_status = ft_pwd(data, command), true);
	else if (!ft_strcmp(command[0], "cd"))
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
		return (data->exit_status = ft_export(data, command), true);
	else if (!ft_strcmp(command[0], "unset"))
		return (true);
	else if (!ft_strcmp(command[0], "env"))
		return (data->exit_status = ft_env(data, command), true);
	else if (!ft_strcmp(command[0], "biman"))
		return (data->exit_status = ft_biman(command), true);
	else
		return (false);
}
