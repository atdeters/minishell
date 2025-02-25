/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:52:51 by adeters           #+#    #+#             */
/*   Updated: 2025/02/25 16:03:53 by vsenniko         ###   ########.fr       */
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
	t_env_lst *tmp;

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

char	**add_path(t_data *data, char **command)
{
	char	**env;
	char	*path_str;
	char	*tmp;
	int		i;

	if (!command)
		return (NULL);
	if (ft_strchr(command[0], '/'))
		return (command);
	path_str = get_pathstr(data);
	env = ft_split(path_str, ':');
	if (!env)
		return (data->error = ERR_SPLIT, NULL);
	i = 0;
	while (env[i])
	{
		tmp = join_path_exe(env[i], command[0]);
		if (!access(tmp, F_OK))
			break ;
		free(tmp);
		i++;
	}
	if (env[i])
		return (free(command[0]), command[0] = tmp, fr_lst(env), command);
	return (fr_lst(env), command);
}
