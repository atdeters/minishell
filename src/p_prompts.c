/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_prompts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:54:44 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 16:57:28 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_prompt(t_data *data)
{
	if (data->exit_status)
		printf("%s%s  ", FAIL_COLOR, PROMPT);
	printf("%s%s  ", SUCC_COLOR, PROMPT);
}

void	p_branch(char *line)
{
	char	*branch;

	branch = ft_strrchr(line, '/') + 1;
	branch = rid_of_nl(branch);
	printf("%sgit:(", GIT_COLOR);
	printf("%s%s", GIT_COLOR_BRANCH, branch);
	printf("%s) ", GIT_COLOR);
}

int	p_folder(void)
{
	char	cwd[PATH_MAX];

	if (SHOW_FOLDER && get_pwd(cwd, true))
		return (1);
	printf("%s%s ", CWD_COLOR, cwd);
	return (0);
}

int	p_git(void)
{
	char	path_buff[PATH_MAX];
	char	path_buff_cur[PATH_MAX];
	char	*git_dir;
	bool	close_flag;

	close_flag = false;
	git_dir = ".git/HEAD";
	if (get_pwd(path_buff, false) || get_pwd(path_buff_cur, false))
		return (1);
	while (access(git_dir, R_OK) != 0)
	{
		chdir("..");
		if (get_pwd(path_buff_cur, false))
			return (chdir(path_buff), 1);
		if (count_slash(path_buff_cur) == 1)
		{
			if (close_flag)
				return (chdir(path_buff), 1);
			close_flag = true;
		}
	}
	if (p_git2(path_buff_cur))
		return (chdir(path_buff), 1);
	return (chdir(path_buff), 0);
}

int	p_git2(char *path)
{
	int		fd;
	char	*line;
	char	*file;

	file = (allo_strcat(path, "/.git/HEAD"));
	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	while (line)
	{
		if (ft_strncmp(line, "ref:", 4) == 0)
			return (p_branch(line), free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}
