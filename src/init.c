/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 20:13:06 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initializing the whole shell program before first command
int	init_shell(t_data *data)
{
	data->exit_status = 0;
	data->env_lst = NULL;
	return (0);
}

// Initializing for every new command
void	init_fd_arr(t_data *data);

int	init_command(t_data *data)
{
	data->n_pipe = 0;
	init_fd_arr(data);
	// Count how many processes are needed -> set data->processes
	// Count how many pipes needed -> set data->pipes_amount
	return (0);
}

void	init_fd_arr(t_data *data)
{
	int	i;

	i = 0;
	while (i < FD_LIMIT)
	{
		data->fd[i][0] = -1;
		data->fd[i][1] = -1;
	}
}
