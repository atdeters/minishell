/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:16:54 by adeters           #+#    #+#             */
/*   Updated: 2025/03/21 18:19:09 by adeters          ###   ########.fr       */
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

int	p_err_biman_invalid(char **command)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd("biman: ", 2);
	ft_putstr_fd(command[1], 2);
	ft_putstr_fd(" is not an existing builtin function.\n", 2);
	return (ERR_INV_BUILTIN);
}

int	ft_biman(t_data *data, char **command)
{
	if (count_opts(command) != 2)
		return (print_usage(data, BIMAN_HELP_FILE_PATH), ERR_BUILTIN_USAGE);
	if (!ft_strcmp(command[1], "echo"))
		return (print_usage(data, ECHO_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "cd"))
		return (print_usage(data, CD_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "pwd"))
		return (print_usage(data, PWD_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "export"))
		return (print_usage(data, EXPORT_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "unset"))
		return (print_usage(data, UNSET_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "env"))
		return (print_usage(data, ENV_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "exit"))
		return (print_usage(data, EXIT_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "alias"))
		return (print_usage(data, ALIAS_HELP_FILE_PATH), 0);
	if (!ft_strcmp(command[1], "biman"))
		return (print_usage(data, BIMAN_HELP_FILE_PATH), 0);
	return (p_err_biman_invalid(command));
}

bool	handle_nc_builtin(t_data *data, char **command)
{
	if (!command[0])
		return (false);
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
		return (ft_export(data, command), true);
	else if (!ft_strcmp(command[0], "unset"))
		return (true);
	else if (!ft_strcmp(command[0], "env"))
		return (data->exit_status = ft_env(data, command), true);
	else if (!ft_strcmp(command[0], "biman"))
		return (data->exit_status = ft_biman(data, command), true);
	else
		return (false);
}
