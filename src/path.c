/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:52:51 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 18:16:11 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path_exe(char *path, char *exe)
{
	char	*tmp;
	char	*res;

	if (!path | !exe)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, exe);
	if (!res)
		return (free(tmp), NULL);
	return (free(tmp), res);
}

char	*get_pathstr(t_data *data)
{
	t_env_lst	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->filed, "PATH",
				ft_strlen(tmp->filed)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**check_env(t_data *data, char **paths_arr, char **command)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths_arr[i])
	{
		tmp = join_path_exe(paths_arr[i], command[0]);
		if (!tmp)
		{
			fr_lst(paths_arr);
			rage_quit(data, ERR_MALLOC, false, NULL);
		}
		if (!access(tmp, F_OK))
			break ;
		free(tmp);
		i++;
	}
	if (paths_arr[i])
		return (free(command[0]), command[0] = tmp, fr_lst(paths_arr), command);
	return (fr_lst(paths_arr), command);
}

char	**add_path(t_data *data, char **command)
{
	char	**paths_arr;
	char	*paths_str;

	if (ft_strchr(command[0], '/'))
		return (command);
	paths_str = get_pathstr(data);
	paths_arr = ft_split(paths_str, ':');
	if (!paths_arr)
		rage_quit(data, ERR_MALLOC, false, NULL);
	return (check_env(data, paths_arr, command));
}
