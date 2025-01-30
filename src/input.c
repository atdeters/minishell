/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/01/30 16:56:21 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_prompt(t_data *data)
{
	if (data->exit_status)
		printf("%s%s  ", FAIL_COLOR, PROMPT);
	printf("%s%s  ", SUCC_COLOR, PROMPT);
}

int	p_folder(void)
{
	char	cwd[PATH_MAX];
	
	if (SHOW_FOLDER && get_pwd(cwd, true))
		return (1);
	printf("%s%s ", CWD_COLOR, cwd);
	return (0);
}

int	get_branch(void)
{
	char	cwd[PATH_MAX];
	int		level;
	int		i;

	level = 0;
	i = 0;
	get_pwd(cwd, false);
	while (cwd[i])
	{
		if (cwd[i] == '/')
			level++;
		i++;
	}
	char *ad = "/sgoinfre/adeters/minishell/.git/HEAD";
	if (access(ad, F_OK) == 0)
		printf("found the file here\n");
	return (1);
}

// not working yet
int	p_git(void)
{
	if (get_branch())
	{
		printf("%sgit:(", GIT_COLOR);
		printf("%s%s", GIT_COLOR_BRANCH, "main");
		printf("%s) ", GIT_COLOR);
	}
	return (0);
}

char	*get_input(t_data *data)
{
	char	*input;

	p_prompt(data);
	if (SHOW_FOLDER && p_folder())
		return (NULL); // Set data->error properly
	if (SHOW_GIT && p_git())
		return (NULL); // Set data->error properly
	input = readline(RESET);
	return (input);
}
