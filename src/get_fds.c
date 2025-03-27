/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:10:32 by adeters           #+#    #+#             */
/*   Updated: 2025/03/27 16:38:52 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_in(t_data *data, int *fd_in)
{
	int	in_m;
	int	i;

	in_m = data->parsed_lst->in_mode;
	*fd_in = -1;
	if (in_m == IN_MODE_STD)
		*fd_in = STDIN_FILENO;
	else if (in_m == IN_MODE_PIPE)
		*fd_in = data->fd_pipe[data->pipe_ind - 1][0];
	else if (in_m == IN_MODE_FILE)
	{
		i = 0;
		while (data->parsed_lst->in_arr[i])
		{
			check_access(data, data->parsed_lst->in_arr[i], true);
			if (*fd_in != -1)
				close(*fd_in);
			*fd_in = open(data->parsed_lst->in_arr[i], O_RDONLY);
			if (*fd_in == -1)
				rage_quit(data, ERR_OPEN, false, data->parsed_lst->in_arr[i]);
			i++;
		}
	}
	return (0);
}

void	check_out_arr(t_data *data, int *fd_out, int open_m)
{
	int	i;

	i = 0;
	while (data->parsed_lst->out_arr[i])
	{
		// TODO: Does not work properly
		if (access(data->parsed_lst->out_arr[i], W_OK) == -1
			&& !access(data->parsed_lst->out_arr[i], F_OK))
			rage_quit(data, ERR_PERM, false, data->parsed_lst->out_arr[i]);
		// TODO: Check valid directory (like ./ instead of just /)
		if (*fd_out != -1)
			close(*fd_out);
		*fd_out = open(data->parsed_lst->out_arr[i], open_m, 0644);
		if (*fd_out == -1)
			rage_quit(data, ERR_OPEN, false, data->parsed_lst->out_arr[i]);
		i++;
	}
}

int	get_fd_out(t_data *data, int *fd_out)
{
	int	out_m;
	int	open_m;

	*fd_out = -1;
	out_m = data->parsed_lst->out_mode;
	if (out_m == OUT_MODE_STD)
		*fd_out = STDOUT_FILENO;
	else if (out_m == OUT_MODE_PIPE)
		*fd_out = data->fd_pipe[data->pipe_ind][1];
	else if (out_m == OUT_MODE_FILE_TR || out_m == OUT_MODE_FILE_APP)
	{
		if (out_m == OUT_MODE_FILE_APP)
			open_m = O_WRONLY | O_CREAT | O_APPEND;
		else
			open_m = O_WRONLY | O_CREAT | O_TRUNC;
		check_out_arr(data, fd_out, open_m);
	}
	return (0);
}

int	get_fds(t_data *data, int *fd_in, int *fd_out)
{
	get_fd_in(data, fd_in);
	get_fd_out(data, fd_out);
	return (0);
}
