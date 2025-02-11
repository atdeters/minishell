/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:27:07 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 17:55:02 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_branch(char *path);
char	*extract_branch(int fd, char *line);

char	*get_git_alloc(void)
{
	char		*path;
	char		*path_tmp;
	static char	*git_dir = ".git/HEAD";
	bool		close_flag;

	close_flag = false;
	path_tmp = get_pwd_alloc(false);
	if (!path_tmp)
		return (NULL);
	path = ft_strdup(path_tmp);
	while (access(git_dir, R_OK) != 0)
	{
		chdir("..");
		path = get_pwd_alloc(false);
		if (!path)
			return (chdir(path_tmp), free(path_tmp), NULL);
		if (count_slash(path) == 1)
		{
			if (close_flag)
				return (chdir(path_tmp), free(path_tmp), free(path), NULL);
			close_flag = true;
		}
		free (path);
	}
	return (chdir(path_tmp), free(path_tmp), create_branch(path));
}

char	*create_branch(char *path)
{
	char	*file;
	char	*line;
	int		fd;

	file = ft_strjoin(path, "/.git/HEAD");
	if (!file)
		return (free(path), NULL);
	free(path);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), NULL);
	while (line)
	{
		if (ft_strncmp(line, "ref:", 4) == 0)
			return (extract_branch(fd, line));
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), NULL);
}
char	*extract_branch(int fd, char *line)
{
	char	*branch;

	branch = ft_strrchr(line, '/') + 1;
	branch = rid_of_nl(branch);
	branch = ft_strdup(branch);
	free (line);
	close (fd);
	return (branch);
}
