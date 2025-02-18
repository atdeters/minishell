/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:52:51 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 16:09:47 by adeters          ###   ########.fr       */
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

char	**add_path(t_data *data, char **command)
{
	char	**env;
	char	*tmp;
	int		i;

	if (ft_strchr(command[0], '/'))
		return (command);
	env = ft_split(data->env_lst, ':');
	if (!env)
		return (data->error = ERR_SPLIT, NULL);
	i = 0;
	while (env[i])
	{
		tmp = join_path_exe(env[i], command[0]);
		if (access(tmp, F_OK))
			break ;
		free(tmp);
		i++;
	}
	if (env[i])
		return (free(command[0]), command[0] = tmp, fr_lst(env), command);
	return (free(tmp), fr_lst(env), command);
}
