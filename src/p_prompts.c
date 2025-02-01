/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_prompts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:54:44 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 19:32:48 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_prompt(t_data *data, char *rl_prompt)
{
	if (data->exit_status)
		ft_strlcpy(rl_prompt, FAIL_COLOR, data->fail_color_len + 1);
	else
		ft_strlcpy(rl_prompt, SUCC_COLOR, data->succ_color_len + 1);
	ft_strcat(rl_prompt, PROMPT);
	ft_strcat(rl_prompt, " ");
}

int	add_folder(char *rl_prompt)
{
	char	cwd[PATH_MAX];

	if (SHOW_FOLDER && get_pwd(cwd, true))
		return (1);
	ft_strcat(rl_prompt, CWD_COLOR);
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
	ft_strcat(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, "git:(");
	ft_strcat(rl_prompt, GIT_COLOR_BRANCH);
	ft_strcat(rl_prompt, branch);
	ft_strcat(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, ") ");
}