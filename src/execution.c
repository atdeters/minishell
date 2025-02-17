/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 19:35:07 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Does currently not free anything that might be allocated anywhere
// Make sure to check for every exit
// Filedescriptors are closed already in the cool_dup
int	execute(t_data *data, int fd_in, int fd_out, char **command)
{
	int	acc_code;

	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	check_access(command, &acc_code);
	if (acc_code)
		exit(acc_code);
	if (data->pid[data->n_pid] == 0)
	{
		if (cool_dup(data, fd_in, fd_out))
			exit (pc_err(ERR_DUP2));
		if (is_builtin(command))
			exit (0);
		if (execve(command[0], command, data->envp) == -1)
			exit(pc_err(ERR_EXECVE));
	}
	data->n_pid++;
	return (0);
}

bool	handle_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", fd_strlen(command[0])))
		return (ft_echo(command), true);
	else if (!ft_strncmp(command[0], "cd", fd_strlen(command[0])))
		return (ft_cd(command), true);
	else if (!ft_strncmp(command[0], "pwd", fd_strlen(command[0])))
		return (ft_pwd(), true);
	else if (!ft_strncmp(command[0], "export", fd_strlen(command[0])))
		return (ft_export(command), true);
	else if (!ft_strncmp(command[0], "unset", fd_strlen(command[0])))
		return (ft_unset(command), true);
	else if (!ft_strncmp(command[0], "env", fd_strlen(command[0])))
		return (ft_env(command), true);
	else if (!ft_strncmp(command[0], "exit", fd_strlen(command[0])))
		return (ft_exit(command), true);
	else
		return (false);
}
