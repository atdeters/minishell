/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:04 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 19:16:43 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pwd_clean_flag(char **command)
{
	if (!command[1])
		return (false);
	if (!ft_strcmp(command[1], "-c"))
		return (true);
	if (!ft_strcmp(command[1], "--clean"))
		return (true);
	return (false);
}

bool	is_pwd_help_flag(char **command)
{
	if (!command[1])
		return (false);
	if (!ft_strcmp(command[1], "-h"))
		return (true);
	if (!ft_strcmp(command[1], "--help"))
		return (true);
	return (false);
}

void	ft_pwd(t_data *data, char **command)
{
	char	*cwd;

	if (!command[1])
		cwd = get_pwd_alloc(data, false);
	else if (is_pwd_clean_flag(command))
		cwd = get_pwd_alloc(data, true);
	else if (is_pwd_help_flag(command))
	{
		print_usage(data, PWD_HELP_FILE_PATH);
		return ;
	}
	if (!cwd)
	{
		ft_putstr_fd(ERR_MSG_FUNC_GETCWD, 2);
		return ;
	}
	else
		printf("%s\n", cwd);
	free(cwd);
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
		tmp = strrchr(cwd, '/');
		if (tmp)
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
