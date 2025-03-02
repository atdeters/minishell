/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:10:32 by adeters           #+#    #+#             */
/*   Updated: 2025/03/01 16:57:38 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// File fds need to be put into the fds_file array so they can be closed
// properly (not that bad right now as they never open in the parent proc)
// Add here_doc
int	get_fd_in(t_data *data, int *fd_in)
{
	int	in_m;

	in_m = data->parsed_lst->in_mode;
	if (in_m == IN_MODE_STD)
		*fd_in = STDIN_FILENO;
	else if (in_m == IN_MODE_PIPE)
		*fd_in = data->fd_pipe[data->pipe_ind - 1][0];
	else if (in_m == IN_MODE_FILE)
	{
		*fd_in = open(data->parsed_lst->in, O_RDONLY);
		if (*fd_in == -1)
			return (setnret(data, ERR_OPEN));
	}
	return (0);
}

int	get_fd_out(t_data *data, int *fd_out)
{
	int		out_m;
	int		open_m;

	out_m = data->parsed_lst->out_mode;
	if (out_m == OUT_MODE_FILE_APP)
		open_m = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_m = O_WRONLY | O_CREAT | O_TRUNC;
	if (out_m == OUT_MODE_STD)
		*fd_out = STDOUT_FILENO;
	else if (out_m == OUT_MODE_PIPE)
		*fd_out = data->fd_pipe[data->pipe_ind][1];
	else if (out_m == OUT_MODE_FILE_TR || out_m == OUT_MODE_FILE_APP)
	{
		*fd_out = open(data->parsed_lst->out, open_m, 0644);
		if (*fd_out == -1)
			return (setnret(data, ERR_OPEN));
	}
	return (0);
}

int	get_fds(t_data *data, int *fd_in, int *fd_out)
{
	if (check_access_files(data))
		return (data->error);
	if (get_fd_in(data, fd_in))
		return (data->error);
	if (get_fd_out(data, fd_out))
		return (data->error);
	return (0);
}
