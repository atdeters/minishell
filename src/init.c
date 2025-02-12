/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/12 18:39:30 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initializing the whole shell program before first command
int	init_shell(t_data *data, char **env)
{
	data->exit_status = 0;
	data->env_lst = NULL;
	data->envp = env;
	return (0);
}

// Initializing for every new command
void	init_fd_arr(t_data *data);
int		pipe_maker(t_data *data);

int	init_command(t_data *data)
{
	data->n_pipe = 0;
	data->n_pid = 0;
	init_fd_arr(data);
	// Count how many processes are needed -> set data->processes
	// Count how many pipes needed -> set data->pipes_amount
	// Use the pipe function on the array of fds
	if (pipe_maker(data))
		return (PIPE_E);
	return (0);
}

void	init_fd_arr(t_data *data)
{
	int	i;

	i = 0;
	while (i < FD_LIMIT)
	{
		data->fd_pipe[i][0] = -1;
		data->fd_pipe[i][1] = -1;
		i++;
	}
}

/**
 * Sets the data->error automatically
 */
int	pipe_maker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipes_amount)
	{
		if (pipe(data->fd_pipe[i]) == -1)
			return (close_all(data), data->error = PIPE, PIPE);
		i++;
	}
	return (0);
}