/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:45:10 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 17:44:07 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd_arr(t_data *data);

int	init_command(t_data *data)
{
	data->n_pipe = -1;
	data->n_pid = 0;
	data->ind_in_pipe = 0;
	data->ind_out_pipe = 0;
	data->error = 0;
	data->token_lst = NULL;
	data->parsed_lst = NULL;
	init_fd_arr(data);
	// Count how many processes are needed -> set data->processes
	// Count how many pipes needed -> set data->pipes_amount
	data->pipes_amount = 0;
	//if (pipe_maker(data))
	//	return (ERR_PIPE);
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
	i = 0;
	while (i < FD_LIMIT * 2)
	{
		data->fd_file[i] = -1;
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
			return (close_all(data), setnret(data, ERR_PIPE));
		i++;
	}
	return (0);
}
