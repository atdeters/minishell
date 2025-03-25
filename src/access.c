/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/03/25 20:18:21 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sys/stat.h"

int	check_access(t_data *data, char *name, bool is_file)
{
	struct stat	path_stat;

	stat(name, &path_stat);
	if (is_builtin(name))
		return (0);
	if (!is_file && access(name, F_OK) == -1)
		rage_quit(data, ERR_ACCESS, false, name);
	else if (access(name, F_OK) == -1)
		rage_quit(data, ERR_ACCESS_FILE, false, name);
	else if (!is_file && access(name, X_OK) == -1)
		rage_quit(data, ERR_PERM, false, name);
	else if (is_file && access(name, R_OK) == -1 && !access(name, F_OK))
		rage_quit(data, ERR_PERM, false, name);
	else if (!is_file && !ft_strchr(name, '/'))
		rage_quit(data, ERR_ACCESS, false, name);
	else if (S_ISDIR(path_stat.st_mode))
		rage_quit(data, ERR_DIR, false, name);
	return (0);
}
