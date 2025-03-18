/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:04 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 15:24:21 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_flag_clean_pwd(char **command)
{
	if (!command[1])
		return (false);
	if (!ft_strcmp(command[1], "-c"))
		return (true);
	if (!ft_strcmp(command[1], "--clean"))
		return (true);
	return (false);
}

bool	has_flag_help_pwd(char **command)
{
	if (!command[1])
		return (false);
	if (!ft_strcmp(command[1], "-h"))
		return (true);
	if (!ft_strcmp(command[1], "--help"))
		return (true);
	return (false);
}

int	ft_pwd(t_data *data, char **command)
{
	char	*cwd;

	if (!command[1])
		cwd = get_pwd_alloc(data, false);
	else if (has_flag_clean_pwd(command))
		cwd = get_pwd_alloc(data, true);
	else
		return (print_usage(data, PWD_HELP_FILE_PATH), ERR_BUILTIN_USAGE);
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
