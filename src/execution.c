/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 19:27:58 by adeters          ###   ########.fr       */
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

void	handle_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", 4))
		ft_echo(command);
	else if (!ft_strncmp(command[0], "cd", 2))
		ft_cd(command);
	else if (!ft_strncmp(command[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(command[0], "export", 6))
		ft_export(command);
	else if (!ft_strncmp(command[0], "unset", 5))
		ft_unset(command);
	else if (!ft_strncmp(command[0], "env", 3))
		ft_env(command);
	else if (!ft_strncmp(command[0], "exit", 4))
		ft_exit(command);
}
