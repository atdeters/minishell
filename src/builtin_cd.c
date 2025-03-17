/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:31:37 by adeters           #+#    #+#             */
/*   Updated: 2025/03/17 14:29:48 by adeters          ###   ########.fr       */
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

// TODO: Still needs to update the PWD env variable!
int	ft_cd(t_data *data, char **command)
{
	if (count_opts(command) > 2)
	{
		ft_putstr_fd(SHELL_ERR_IDENT, 2);
		ft_putstr_fd(ERR_MSG_CD_ARGS, 2);
		return (ERR_CD_USAGE);
	}
	if (!command[1] && chdir(data->home_path) == -1)
		rage_quit(data, ERR_CHDIR, true, NULL);
	replace_home(data, command);
	if (command[1] && chdir(command[1]) == -1)
		return (ERR_INVALID_PATH);
	return (0);
}
