/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:45:30 by adeters           #+#    #+#             */
/*   Updated: 2025/03/01 17:10:09 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if we can rage quit the program if there is a function that is not
// the last one being a critical error
int	wait_all(t_data *data)
{
	int		i;
	bool	quit;
	int		quit_code;

	i = 0;
	quit = false;
	while (i < data->n_pid)
	{
		waitpid(data->pid[i], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		if (data->exit_status / 100 == 2)
		{
			quit = true;
			quit_code = data->exit_status;
		}
		i++;
	}
	if (quit)
		rage_quit(data, quit_code, true, NULL);
	return (data->exit_status);
}

int	cool_dup(t_data *data, int fd_in, int fd_out)
{
	if (fd_in != 0 && dup2(fd_in, STDIN_FILENO) == -1)
		rage_quit(data, ERR_DUP2, false, NULL);
	if (fd_out != 1 && dup2(fd_out, STDOUT_FILENO) == -1)
		rage_quit(data, ERR_DUP2, false, NULL);
	if (data->parsed_lst->out_mode != OUT_MODE_PIPE && fd_out != 1)
		close (fd_out);
	if (data->parsed_lst->in_mode != IN_MODE_PIPE && fd_in != 0)
		close (fd_in);	
	close_all(data);
	return (0);
}
