/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prompts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:54:44 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 21:03:42 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_prompt(t_data *data, char *rl_prompt)
{
	if (data->exit_status)
		start_ansi(rl_prompt, FAIL_COLOR);
	else
		start_ansi(rl_prompt, SUCC_COLOR);
	ft_strcat(rl_prompt, PROMPT);
	ft_strcat(rl_prompt, "  ");
}

int	add_folder(char *rl_prompt)
{
	char	cwd[PATH_MAX];

	if (SHOW_FOLDER && get_pwd(cwd, true))
		return (1);
	add_ansi(rl_prompt, CWD_COLOR);
	ft_strcat(rl_prompt, cwd);
	ft_strcat(rl_prompt, " ");
	return (0);
}

int	add_git(char *rl_prompt)
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
	if (add_git2(path_buff_cur, rl_prompt))
		return (chdir(path_buff), 1);
	return (chdir(path_buff), 0);
}

int	add_git2(char *path, char *rl_prompt)
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
			return (add_branch(line, rl_prompt), free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

void	add_branch(char *line, char *rl_prompt)
{
	char	*branch;

	branch = ft_strrchr(line, '/') + 1;
	branch = rid_of_nl(branch);
	add_ansi(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, "git:(");
	add_ansi(rl_prompt, GIT_COLOR_BRANCH);
	ft_strcat(rl_prompt, branch);
	add_ansi(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, ") ");
}
