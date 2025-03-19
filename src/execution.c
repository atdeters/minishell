/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/03/19 18:07:52 by adeters          ###   ########.fr       */
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

	signal(SIGINT, signal_handler);
	parser_env_into_arr(data);
	add_path(data, command);
	get_fds(data, &fd_in, &fd_out);
	check_access(data, command[0], false);
	cool_dup(data, fd_in, fd_out);
	if (handle_builtin(data, command))
		rage_quit(data, data->exit_status, false, NULL);
	if (execve(command[0], command, data->envp) == -1)
		rage_quit(data, ERR_EXECVE, false, NULL);
	return (0);
}

int	execute(t_data *data)
{
	char	**command;

	if (data->parsed_lst)
		command = data->parsed_lst->cmd_and_args;
	else
		return (0);
	if (data->pipes_amount == 0 && handle_nc_builtin(data, command))
		return (0);
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		rage_quit(data, ERR_FORK, true, NULL);
	if (data->pid[data->n_pid] == 0)
		execute_subshell(data, command);
	data->n_pid++;
	return (0);
}
