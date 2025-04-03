/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/04/03 14:13:38 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sys/stat.h"

void	check_access_infile(t_data *data, char *filename)
{
	struct stat	path_stat;

	if (stat(filename, &path_stat) == -1 && errno == EACCES)
		rage_quit(data, ERR_PERM, false, filename);
	if (!access(filename, F_OK) && access(filename, R_OK) == -1)
		rage_quit(data, ERR_PERM, false, filename);
	if (access(filename, F_OK) == -1)
		rage_quit(data, ERR_ACCESS_FILE, false, filename);
	if (S_ISDIR(path_stat.st_mode))
		rage_quit(data, ERR_DIR, false, filename);
}

void	check_access_outfile(t_data *data, char *filename)
{
	struct stat	path_stat;

	if (stat(filename, &path_stat) == -1 && errno == EACCES)
		rage_quit(data, ERR_PERM, false, filename);
	if (!access(filename, F_OK) && access(filename, W_OK) == -1)
		rage_quit(data, ERR_PERM, false, filename);
	if (!access(filename, F_OK) && S_ISDIR(path_stat.st_mode))
		rage_quit(data, ERR_DIR, false, filename);
}

void	check_access_command(t_data *data, char *command)
{
	struct stat	path_stat;

	if (is_builtin(command))
		return ;
	if (!ft_strchr(command, '/'))
		rage_quit(data, ERR_ACCESS, false, command);
	if (stat(command, &path_stat) == -1 && errno == EACCES)
		rage_quit(data, ERR_PERM, false, command);
	if (path_stat.st_size == 0)
		rage_quit(data, 0, false, NULL);
	if (!access(command, F_OK) && access(command, X_OK) == -1)
		rage_quit(data, ERR_PERM, false, command);
	if (access(command, F_OK) == -1)
		rage_quit(data, ERR_ACCESS, false, command);
	if (S_ISDIR(path_stat.st_mode))
		rage_quit(data, ERR_DIR, false, command);
}
