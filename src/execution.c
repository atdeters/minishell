/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 19:50:33 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_nc_builtin(char **command);

// Add here_doc
int	get_fd_in(t_data *data, int *fd_in)
{
	int	in_m;

	in_m = data->parsed_lst->in_mode;
	if (in_m == IN_MODE_STD)
		*fd_in = STDIN_FILENO;
	else if (in_m == IN_MODE_PIPE)
		*fd_in = data->fd_pipe[data->ind_in_pipe - 1][0];
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
		*fd_out = data->fd_pipe[data->ind_out_pipe - 1][1];
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

int	execute_subshell(t_data *data, char **command)
{
	int		fd_in;
	int		fd_out;
	
	add_path(data, command);
	if (get_fds(data, &fd_in, &fd_out))
		rage_quit(data, data->error);
	if (check_access(data, command[0], false))
		rage_quit(data, data->error);
	if (cool_dup(data, fd_in, fd_out))
	{
		pc_err(ERR_DUP2);
		rage_quit(data, data->error);
	}
	if (handle_builtin(data, command))
		rage_quit(data, 0);
	if (execve(command[0], command, data->envp) == -1)
	{
		pc_err(ERR_EXECVE);
		rage_quit(data, data->error);
	}
	return (0);
}

int	execute(t_data *data)
{
	char	**command;

	if (data->parsed_lst->out_mode == OUT_MODE_PIPE)
		data->ind_out_pipe++;
	if (data->parsed_lst->in_mode == IN_MODE_PIPE)
		data->ind_in_pipe++;
	command = data->parsed_lst->cmd_and_args;
	if (data->pipes_amount == 0 && handle_nc_builtin(command))
		return (0);
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
		execute_subshell(data, command);
	data->n_pid++;
	return (0);
}

bool	handle_nc_builtin(char **command)
{
	if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		return (ft_cd(command), true);
	return (false);
}

bool	handle_builtin(t_data *data, char **command)
{
	(void)data; // just to mute compiler
	if (!ft_strncmp(command[0], "echo", ft_strlen(command[0])))
		return (ft_echo(command), true);
	else if (!ft_strncmp(command[0], "pwd", ft_strlen(command[0])))
		return (ft_pwd(), true);


	// nc_builtins dont have to be done here
	if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		return (true);
	// else if (!ft_strncmp(command[0], "export", ft_strlen(command[0])))
	// 	return (ft_export(command), true);
	// else if (!ft_strncmp(command[0], "unset", ft_strlen(command[0])))
	// 	return (ft_unset(command), true);
	// else if (!ft_strncmp(command[0], "env", ft_strlen(command[0])))
	// 	return (ft_env(data), true);
	// else if (!ft_strncmp(command[0], "exit", ft_strlen(command[0])))
	// 	return (ft_exit(command), true);
	else
		return (false);
}
