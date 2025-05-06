/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:45:10 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_fd_arr(t_data *data);

void	init_command(t_data *data)
{
	g_signal = 0;
	data->n_pid = 0;
	data->pipe_ind = 0;
	data->p_err = true;
	data->error = 0;
	data->pipes_amount = 0;
	data->token_lst = NULL;
	data->parsed_lst = NULL;
	data->input = NULL;
	data->hdf_arr = NULL;
	data->prog_path = NULL;
	init_fd_arr(data);
	set_shlvl(data, &data->env_lst, 0);
	data->pipes_amount = 0;
	data->quotes_flag = true;
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

int	pipe_maker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipes_amount)
	{
		if (pipe(data->fd_pipe[i]) == -1)
		{
			close_all(data);
			rage_quit(data, ERR_PIPE, true, NULL);
		}
		i++;
	}
	return (0);
}
