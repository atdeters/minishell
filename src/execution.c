/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:34:50 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 13:16:53 by adeters          ###   ########.fr       */
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

char	*get_value_from_lst(t_env_lst *lst, char *key)
{
	t_env_lst	*tmp;
	char		*value;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->filed))
		{
			value = ft_strdup(tmp->value);
			if (!value)
				return (NULL);
			return (value);
		}
		tmp = tmp->next;
	}
	return (key);
}

char **lst_join(char **lst1, char **lst2)
{
	int		fields;
	int		i;
	int		j;
	char	**new;

	if (!lst1 | !lst2)
		return (NULL);
	while (lst1[i++])
		fields++;
	i = 0;
	while (lst2[i++])
		fields++;
	fields++;
	new = malloc(fields * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (lst1[i++])
		new[j++] = lst1[i];
	i = 0;
	while (lst2[i++])
		new[j++] = lst2[i];
	return (new);
}

int	replace_alias(t_data *data, char **command)
{
	char	*alias;
	char	**add_commands;
	char	**new_com;
	char	*tmp;

	alias = command[0];
	tmp = get_value_from_lst(data->alias_lst, command[0]);
	if (!tmp)
		return (1);
	if (ft_strcmp(command[0], tmp))
	{
		rid_of_nl(tmp);
		add_commands = ft_split(tmp, ' ');
		free (tmp);
		if (!add_commands)
			rage_quit(data, ERR_SPLIT, true);
		new_com = lst_join(add_commands, command);
		ft_lst(add_commands);
		if (!new_com)
			rage_quit(data, ERR_MALLOC, true);
		fr_lst(command);
		command = new_com;
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
	if (replace_alias(data, command))
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
