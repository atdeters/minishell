/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/03/25 20:03:19 by adeters          ###   ########.fr       */
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

	signal(SIGINT, sig_handle_basic);
	get_fds(data, &fd_in, &fd_out);
	if (!command[0])
	{
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
		rage_quit(data, 0, false, NULL);
	}
	parser_env_into_arr(data);
	data->prog_path = add_path(data, command);
	if (!data->prog_path)
		rage_quit(data, ERR_MALLOC, false, NULL);
	check_access(data, data->prog_path, false);
	cool_dup(data, fd_in, fd_out);
	if (handle_builtin(data, command))
		rage_quit(data, data->exit_status, false, NULL);
	if (execve(data->prog_path, command, data->envp) == -1)
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
