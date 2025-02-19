/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 15:43:46 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Add here_doc
int	get_fd_in(t_data *data, int *fd_in)
{
	int	in_m;

	in_m = data->parsed_lst->in_mode;
	if (in_m == IN_MODE_STD)
		*fd_in = STDIN_FILENO;
	else if (in_m == IN_MODE_PIPE)
	{
		*fd_in = data->fd_pipe[data->n_pipe][0];
		data->n_pipe++;
	}
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
	char	*outfile;

	out_m = data->parsed_lst->out_mode;
	outfile = data->parsed_lst->out;
	if (out_m == OUT_MODE_FILE_APP)
		open_m = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_m = O_WRONLY | O_CREAT | O_TRUNC;
	if (out_m == OUT_MODE_STD)
		*fd_out = STDOUT_FILENO;
	else if (out_m == OUT_MODE_PIPE)
		*fd_out = data->fd_pipe[data->n_pipe - 1][0];
	else if (out_m == OUT_MODE_FILE_TR || out_m == OUT_MODE_FILE_APP)
	{
		*fd_out = open(data->parsed_lst->out, open_m, 0644);
		if (*fd_out == -1)
			return (setnret(data, ERR_OPEN));
	}
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

// Does currently not free anything that might be allocated anywhere
// Make sure to check for every exit
// Filedescriptors are closed already in the cool_dup
int	execute(t_data *data)
{
	int		fd_in;
	int		fd_out;
	char	**command;

	command = data->parsed_lst->cmd_and_args;
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
	{
		if (get_fds(data, &fd_in, &fd_out))
			exit(data->error);
		if (check_access(data, command[0], false))
			exit(data->error);
		if (cool_dup(data, fd_in, fd_out))
			exit (pc_err(ERR_DUP2));
		if (handle_builtin(command))
			exit (0);
		if (execve(command[0], command, data->envp) == -1)
			exit(pc_err(ERR_EXECVE));
	}
	data->n_pid++;
	return (0);
}

bool	handle_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", ft_strlen(command[0])))
		return (ft_echo(command), true);
	else if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		return (ft_cd(command), true);
	else if (!ft_strncmp(command[0], "pwd", ft_strlen(command[0])))
		return (ft_pwd(), true);
	// else if (!ft_strncmp(command[0], "export", ft_strlen(command[0])))
	// 	return (ft_export(command), true);
	// else if (!ft_strncmp(command[0], "unset", ft_strlen(command[0])))
	// 	return (ft_unset(command), true);
	// else if (!ft_strncmp(command[0], "env", ft_strlen(command[0])))
	// 	return (ft_env(command), true);
	// else if (!ft_strncmp(command[0], "exit", ft_strlen(command[0])))
	// 	return (ft_exit(command), true);
	else
		return (false);
}
