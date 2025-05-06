/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:31:37 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:12:06 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_home(t_data *data, char **command)
{
	int		path_size;
	char	*new;

	if (!command[1])
		return (NULL);
	if (count_char(command[1], '~') != 1 && command[1][0] != '~')
		return (command[1]);
	path_size = ft_strlen(command[1]) + ft_strlen(data->home_path) + 1;
	new = calloc(path_size, sizeof(char));
	if (!new)
		rage_quit(data, ERR_MALLOC, true, NULL);
	ft_strcpy(new, data->home_path);
	ft_strcat(new, command[1] + 1);
	free (command[1]);
	command[1] = new;
	return (command[1]);
}

int	p_err_cd(char *command, t_data *data)
{
	if (errno == EACCES)
		return (p_err_arg(ERR_PERM, command));
	if (errno == ENOENT)
		return (p_err_arg(ERR_ACCESS_FILE, command));
	if (errno == ENOTDIR)
		return (p_err_arg(ERR_NOTDIR, command));
	data->p_err = false;
	return (perror("minishell: cd"),
		rage_quit(data, ERR_CHDIR, true, NULL), 1);
}

char	*make_parent_dir(t_data *data, char **command)
{
	char	*parent;
	int		index;

	parent = get_pwd_alloc(data, false);
	if (!parent)
		return (NULL);
	if (count_char(parent, '/') > 1)
	{
		index = ft_strrchr(parent, '/') - parent;
		parent[index] = '\0';
		free(command[1]);
		command[1] = parent;
		return (parent);
	}
	free (parent);
	return (command[1]);
}

char	*make_last_dir(t_data *data, char **command)
{
	t_env_lst	*tmp;
	char		*old;

	tmp = data->env_lst;
	while (tmp && ft_strcmp(tmp->filed, "OLDPWD"))
		tmp = tmp->next;
	if (tmp)
	{
		old = ft_strdup(tmp->value);
		if (!old)
			return (NULL);
		free(command[1]);
		command[1] = old;
		return (old);
	}
	return (command[1]);
}

int	ft_cd(t_data *data, char **command)
{
	if (count_opts(command) > 2)
	{
		ft_putstr_fd(SHELL_ERR_IDENT, 2);
		ft_putstr_fd(ERR_MSG_CD_ARGS, 2);
		return (ERR_BUILTIN_USAGE);
	}
	if (!command[1] && chdir(data->home_path) == -1)
		rage_quit(data, ERR_CHDIR, true, NULL);
	replace_home(data, command);
	if (!ft_strcmp(command[1], "-") && !make_last_dir(data, command))
		rage_quit(data, ERR_MALLOC, true, NULL);
	if (!ft_strcmp(command[1], "..") && !make_parent_dir(data, command))
		rage_quit(data, ERR_MALLOC, true, NULL);
	if (command[1] && chdir(command[1]) == -1)
		return (p_err_cd(command[1], data));
	replace_pwd_env(data);
	return (0);
}
