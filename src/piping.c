/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:45:30 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 16:05:47 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_pid - 1)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
	waitpid(data->pid[i], &data->wstatus, 0);
	if (WIFEXITED(data->wstatus))
		return (WEXITSTATUS(data->wstatus));
	return (1);
}

void	close_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipes_amount)
	{
		if (data->fd_pipe[i][0] != -1)
			close (data->fd_pipe[i][0]);
		if (data->fd_pipe[i][1] != -1)
			close (data->fd_pipe[i][1]);
		i++;
	}
}

int	cool_dup(t_data *data, int fd_in, int fd_out)
{
	if (fd_in != 0 && dup2(fd_in, STDIN_FILENO) == -1)
		return (1);
	if (fd_out != 1 && dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);
	close_all(data);
	return (0);
}
