/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:45:30 by adeters           #+#    #+#             */
/*   Updated: 2025/05/12 17:26:33 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// List might not be complete at this point!!
bool	err_is_critical(int code)
{
	if (code == ERR_MALLOC)
		return (true);
	if (code == ERR_OPEN)
		return (true);
	if (code == ERR_EXECVE)
		return (true);
	if (code == ERR_DUP2)
		return (true);
	return (false);
}

static void	check_sigquit(int exit_status)
{
	int	sig;

	if (WIFSIGNALED(exit_status))
	{
		sig = WTERMSIG(exit_status);
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		if (sig == SIGINT)
			printf("\n");
	}
}

int	wait_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_pid)
	{
		waitpid(data->pid[i], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		check_sigquit(data->exit_status);
		i++;
	}
	return (data->exit_status);
}

int	cool_dup(t_data *data, int fd_in, int fd_out)
{
	if (fd_in != 0 && dup2(fd_in, STDIN_FILENO) == -1)
	{
		close (fd_out);
		close (fd_in);
		rage_quit(data, ERR_DUP2, false, NULL);
	}
	if (fd_out != 1 && dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close (fd_out);
		close (fd_in);
		rage_quit(data, ERR_DUP2, false, NULL);
	}
	if (data->parsed_lst->out_mode != OUT_MODE_PIPE && fd_out != 1)
		close (fd_out);
	if (data->parsed_lst->in_mode != IN_MODE_PIPE && fd_in != 0)
		close (fd_in);
	close_all(data);
	return (0);
}
