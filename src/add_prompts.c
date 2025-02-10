/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prompts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:54:44 by adeters           #+#    #+#             */
/*   Updated: 2025/02/10 18:08:48 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_prompt(t_data *data, char *rl_prompt)
{
	if (!rl_prompt)
		return (NULL);
	if (data->exit_status)
		start_ansi(rl_prompt, FAIL_COLOR);
	else
		start_ansi(rl_prompt, SUCC_COLOR);
	ft_strcat(rl_prompt, PROMPT);
	ft_strcat(rl_prompt, PROMPT_SPACE);
	return (rl_prompt);
}

char	*add_folder(char *rl_prompt, char *path)
{
	if (!rl_prompt)
		return (NULL);
	add_ansi(rl_prompt, CWD_COLOR);
	ft_strcat(rl_prompt, path);
	ft_strcat(rl_prompt, FOLDER_SPACE);
	return (rl_prompt);
}

char	*get_git_alloc(void)
{
	char	*path;
	char	*path_tmp;
	char	*git_dir;
	bool	close_flag;

	close_flag = false;
	git_dir = ".git/HEAD";

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
	chdir(path_tmp);
	free(path_tmp);

	char	*file;
	char	*line;
	char	*branch;
	int		fd;

	file = allo_strcat(path, "/.git/HEAD");
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
		{
			branch = ft_strrchr(line, '/') + 1;
			branch = rid_of_nl(branch);
			branch = ft_strdup(branch);
			return (free(line), close(fd), branch);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), NULL);
}




// int	add_git2(char *path)
// {
// 	int		fd;
// 	char	*line;
// 	char	*file;

// 	file = (allo_strcat(path, "/.git/HEAD"));
// 	if (!file)
// 		return (1);
// 	fd = open(file, O_RDONLY);
// 	free(file);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	if (!line)
// 		return (close(fd), 1);
// 	while (line)
// 	{
// 		if (ft_strncmp(line, "ref:", 4) == 0)
// 			return (add_branch(line, rl_prompt), free(line), close(fd), 0);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (close(fd), 1);
// }





char	*add_branch(char *rl_prompt, char *branch)
{
	if (!rl_prompt)
		return (NULL);
	add_ansi(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, "git:(");
	add_ansi(rl_prompt, GIT_COLOR_BRANCH);
	ft_strcat(rl_prompt, branch);
	add_ansi(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, ") ");
	return (rl_prompt);
}
