/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:04 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	has_flag_clean_pwd(char **command)
{
	int	i;

	if (!command[1])
		return (false);
	if (!ft_strcmp(command[1], "--clean"))
		return (true);
	if (command[1][0] == '-')
	{
		i = 1;
		while (command[1][i])
		{
			if (command[1][i] != 'c')
				return (false);
			i++;
		}
	}
	else
		return (false);
	return (true);
}

int	ft_pwd(t_data *data, char **command)
{
	char	*cwd;

	if (!command[1])
		cwd = get_pwd_alloc(data, false);
	else if (has_flag_clean_pwd(command))
		cwd = get_pwd_alloc(data, true);
	else
		return (p_use_pwd(), ERR_BUILTIN_USAGE);
	printf("%s\n", cwd);
	return (free(cwd), 0);
}

char	*get_pwd_alloc(t_data *data, bool clean)
{
	char	*tmp;
	char	*cwd;
	char	*cl_buff;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		rage_quit(data, ERR_GETCWD, true, NULL);
	if (clean == true)
	{
		tmp = ft_strrchr(cwd, '/');
		if (tmp && ft_strlen(cwd) > 1)
			tmp++;
		else
			tmp = cwd;
		cl_buff = ft_strdup(tmp);
		if (!cl_buff)
		{
			free (cwd);
			rage_quit(data, ERR_MALLOC, true, NULL);
		}
		return (free(cwd), cl_buff);
	}
	else
		return (cwd);
}
