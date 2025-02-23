/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:45:30 by adeters           #+#    #+#             */
/*   Updated: 2025/02/23 15:41:02 by adeters          ###   ########.fr       */
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
	waitpid(data->pid[i], &data->exit_status, 0);
	if (WIFEXITED(data->exit_status))
	{
		data->exit_status = WEXITSTATUS(data->exit_status);
		return (data->exit_status);
	}
	return (1);
}

int	cool_dup(t_data *data, int fd_in, int fd_out)
{
	if (fd_in != 0 && dup2(fd_in, STDIN_FILENO) == -1)
		return (close_all(data), 1);
	if (fd_out != 1 && dup2(fd_out, STDOUT_FILENO) == -1)
		return (close_all(data), 1);
	close_all(data);
	return (0);
}
