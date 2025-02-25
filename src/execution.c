/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/25 10:47:47 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_nc_builtin(t_data *data, char **command);

// Check for the ERR_CHILD that it is always correct or the prog will quit
// for non crititcal errors
int	execute_subshell(t_data *data, char **command)
{
	int		fd_in;
	int		fd_out;

	add_path(data, command);
	if (get_fds(data, &fd_in, &fd_out))
		rage_quit(data, ERR_CHILD, false);
	if (check_access(data, command[0], false))
		rage_quit(data, data->error, false);
	if (cool_dup(data, fd_in, fd_out))
	{
		pc_err(ERR_DUP2);
		rage_quit(data, ERR_CHILD, false);
	}
	if (handle_builtin(data, command))
		rage_quit(data, 0, false);
	if (execve(command[0], command, data->envp) == -1)
	{
		pc_err(ERR_EXECVE);
		rage_quit(data, data->error, false);
	}
	return (0);
}

// char	**replace_alias(t_data *data, char **command)
// {
// 	char	*alias;
// 	char	**rep_com;
// 	char	**new_com;
// 	char	*tmp;

// 	alias = command[0];
// 	tmp = get_value_from_lst(data->alias_lst, command[0]);
// 	if (!tmp)
// 		return (NULL);
// 	if (ft_strcmp(command[0], tmp))
// 	{
// 		rid_of_nl(tmp);
// 		rep_com = ft_split(tmp, ' ');
// 		free (tmp);
// 		if (!rep_com)
// 			rage_quit(data, ERR_SPLIT, true);
// 		new_com = lst_join(rep_com, command + 1);
// 		fr_lst(rep_com);
// 		if (!new_com)
// 			rage_quit(data, ERR_MALLOC, true);
// 		fr_lst(command);
// 		command = new_com;
// 	}
// 	return (command);
// }

int	execute(t_data *data)
{
	char	**command;

	if (data->parsed_lst->out_mode == OUT_MODE_PIPE)
		data->ind_out_pipe++;
	if (data->parsed_lst->in_mode == IN_MODE_PIPE)
		data->ind_in_pipe++;
	command = data->parsed_lst->cmd_and_args;
	// command = replace_alias(data, data->parsed_lst->cmd_and_args);
	if (!command)
		rage_quit(data, ERR_MALLOC, true);
	if (data->pipes_amount == 0 && handle_nc_builtin(data, command))
		return (0);
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
		execute_subshell(data, command);
	data->n_pid++;
	return (0);
}
