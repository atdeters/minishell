/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 13:29:39 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data, int fd_in, int fd_out, char **command)
{
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
	{
		if (cool_dup(data, fd_in, fd_out))
			return (pc_err(ERR_DUP2));
		if (execve(command[0], command, data->envp) == -1)
			exit(pc_err(ERR_EXECVE));
	}
	data->n_pid++;
	return (0);
}

bool	is_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", 4))
		return (true);
	if (!ft_strncmp(command[0], "cd", 2))
		return (true);
	if (!ft_strncmp(command[0], "pwd", 3))
		return (true);
	if (!ft_strncmp(command[0], "export", 6))
		return (true);
	if (!ft_strncmp(command[0], "unset", 5))
		return (true);
	if (!ft_strncmp(command[0], "env", 3))
		return (true);
	if (!ft_strncmp(command[0], "exit", 4))
		return (true);
	return (false);
}
