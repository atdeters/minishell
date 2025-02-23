/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/23 17:58:34 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_nc_builtin(char **command);

// Check for the ERR_CHILD that it is always correct or the prog will quit
// for non crititcal errors
int	execute_subshell(t_data *data, char **command)
{
	int		fd_in;
	int		fd_out;

	add_path(data, command);
	if (get_fds(data, &fd_in, &fd_out))
		rage_quit(data, ERR_CHILD, false);
	if (check_access(data, command[0], false))
		rage_quit(data, data->error, false);
	if (cool_dup(data, fd_in, fd_out))
	{
		pc_err(ERR_DUP2);
		rage_quit(data, ERR_CHILD, false);
	}
	if (handle_builtin(data, command))
		rage_quit(data, 0, false);
	if (execve(command[0], command, data->envp) == -1)
	{
		pc_err(ERR_EXECVE);
		rage_quit(data, data->error, false);
	}
	return (0);
}

int	execute(t_data *data)
{
	char	**command;

	if (data->parsed_lst->out_mode == OUT_MODE_PIPE)
		data->ind_out_pipe++;
	if (data->parsed_lst->in_mode == IN_MODE_PIPE)
		data->ind_in_pipe++;
	command = data->parsed_lst->cmd_and_args;
	if (data->pipes_amount == 0 && handle_nc_builtin(command))
		return (0);
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
		execute_subshell(data, command);
	data->n_pid++;
	return (0);
}

bool	handle_nc_builtin(char **command)
{
	if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		return (ft_cd(command), true);
	// "export" and "alias" are nc_builtins when they have
	// other option. Else they can not be used in a child
	return (false);
}
bool	handle_builtin(t_data *data, char **command)
{
	(void)data; // just to mute compiler
	if (!ft_strncmp(command[0], "echo", ft_strlen(command[0])))
		return (ft_echo(command), true);
	else if (!ft_strncmp(command[0], "pwd", ft_strlen(command[0])))
		return (ft_pwd(), true);
	// nc_builtins dont have to be done here
	if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		return (true);
	// else if (!ft_strncmp(command[0], "export", ft_strlen(command[0])))
	// 	return (ft_export(command), true);
	// else if (!ft_strncmp(command[0], "alias", ft_strlen(command[0])))
	// 	return (ft_export(command), true);
	// else if (!ft_strncmp(command[0], "unset", ft_strlen(command[0])))
	// 	return (ft_unset(command), true);
	// else if (!ft_strncmp(command[0], "env", ft_strlen(command[0])))
	// 	return (ft_env(data), true);
	// else if (!ft_strncmp(command[0], "exit", ft_strlen(command[0])))
	// 	return (ft_exit(command), true);
	else
		return (false);
}
