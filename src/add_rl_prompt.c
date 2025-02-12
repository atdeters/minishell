/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prompts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:54:44 by adeters           #+#    #+#             */
/*   Updated: 2025/02/12 19:58:51 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*start_ansi(char *rl_prompt, char *color)
{
	if (!rl_prompt)
		return (NULL);
	ft_strcpy(rl_prompt, "\001");
	ft_strcat(rl_prompt, color);
	ft_strcat(rl_prompt, "\002");
	return (rl_prompt);
}

char	*add_ansi(char *rl_prompt, char *color)
{
	if (!rl_prompt)
		return (NULL);
	ft_strcat(rl_prompt, "\001");
	ft_strcat(rl_prompt, color);
	ft_strcat(rl_prompt, "\002");
	return (rl_prompt);
}

char	*add_prompt(t_data *data, char *rl_prompt)
{
	if (!rl_prompt)
		return (NULL);
	if (SHOW_EXIT_COL && data->exit_status)
	{
		start_ansi(rl_prompt, FAIL_COLOR);
		ft_strcat(rl_prompt, PROMPT);
	}
	else if (SHOW_EXIT_COL)
	{
		start_ansi(rl_prompt, SUCC_COLOR);
		ft_strcat(rl_prompt, PROMPT);
	}
	else
		ft_strcpy(rl_prompt, PROMPT);
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

char	*add_branch(char *rl_prompt, char *branch)
{
	if (!rl_prompt)
		return (NULL);
	add_ansi(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, "git:(");
	add_ansi(rl_prompt, GIT_COLOR_BRANCH);
	ft_strcat(rl_prompt, branch);
	add_ansi(rl_prompt, GIT_COLOR);
	ft_strcat(rl_prompt, ")");
	ft_strcat(rl_prompt, GIT_SPACE);
	return (rl_prompt);
}
