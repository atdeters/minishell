/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/03/01 16:59:49 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_nc_builtin(t_data *data, char **command);

// Check for the ERR_CHILD that it is always correct or the prog will quit
// for non crititcal errors
int	execute_subshell(t_data *data, char **command)
{
	int		fd_in;
	int		fd_out;

	add_path(data, command);
	if (get_fds(data, &fd_in, &fd_out))
		rage_quit(data, ERR_CHILD, false, NULL);
	if (check_access(data, command[0], false))
		rage_quit(data, data->error, false, NULL);
	if (cool_dup(data, fd_in, fd_out))
	{
		pc_err(ERR_DUP2);
		rage_quit(data, ERR_CHILD, false, NULL);
	}
	if (handle_builtin(data, command))
		rage_quit(data, 0, false, NULL);
	if (execve(command[0], command, data->envp) == -1)
	{
		pc_err(ERR_EXECVE);
		rage_quit(data, data->error, false, NULL);
	}
	return (0);
}

int	execute(t_data *data)
{
	char	**command;

	command = data->parsed_lst->cmd_and_args;
	if (!command)
		rage_quit(data, ERR_MALLOC, true, NULL); // ?
	if (data->pipes_amount == 0 && handle_nc_builtin(data, command))
		return (0);
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
		execute_subshell(data, command);
	data->n_pid++;
	return (0);
}
