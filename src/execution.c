/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/03/31 15:34:18 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_and_quit(t_data *data, int fd_in, int fd_out)
{
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	rage_quit(data, 0, false, NULL);
}

int	execute_subshell(t_data *data, char **cmd)
{
	int	fd_in;
	int	fd_out;

	signal(SIGINT, sig_handle_basic);
	get_fds(data, &fd_in, &fd_out);
	if (!cmd[0])
		close_fd_and_quit(data, fd_in, fd_out);
	parser_env_into_arr(data);
	data->prog_path = add_path(data, cmd);
	if (!data->prog_path)
		rage_quit(data, ERR_MALLOC, false, NULL);
	check_access_command(data, data->prog_path);
	cool_dup(data, fd_in, fd_out);
	if (handle_builtin(data, cmd))
		rage_quit(data, data->exit_status, false, NULL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(data->prog_path, cmd, data->envp) == -1 && errno == ENOEXEC)
		rage_quit(data, 0, false, NULL);
	else
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
