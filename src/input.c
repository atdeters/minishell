/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 16:58:39 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculates the length that is needed for the full rl_prompt.
 * 
 * It also includes the safety shell that ansi-escape sequences are 
 * surrounded with (aka the "\001" and "\002"). The ANSI_SHELL_LEN macro takes
 * care of that.
 */
int	rl_prompt_len(t_data *data, char *path, char *branch)
{
	int	len;

	len = 0;
	if (SHOW_EXIT_COL && data->exit_status)
		len += ft_strlen(FAIL_COLOR) + ANSI_SHELL_LEN;
	else if (SHOW_EXIT_COL)
		len += ft_strlen(SUCC_COLOR) + ANSI_SHELL_LEN;
	len += ft_strlen(PROMPT);
	len += ft_strlen(PROMPT_SPACE);
	if (SHOW_FOLDER && path)
	{
		len += ft_strlen(CWD_COLOR) + ANSI_SHELL_LEN;
		len += ft_strlen(path);
		len += ft_strlen(FOLDER_SPACE);
	}
	if (SHOW_GIT && branch)
	{
		len += ft_strlen((GIT_COLOR) + ANSI_SHELL_LEN) * 2;
		len += ft_strlen(GIT_COLOR_BRANCH) + ANSI_SHELL_LEN;
		len += ft_strlen(branch);
		len += GIT_LEN_NO_BRANCH;
		len += ft_strlen(GIT_SPACE);
	}
	len += ft_strlen(RESET) + ANSI_SHELL_LEN;
	return (len);
}

/**
 * @brief Little helper function to free the paramters put into it
 */
void	clear_input_func(char *rl_prompt, char *path, char *branch)
{
	if (path)
		free (path);
	if (branch)
		free (branch);
	if (rl_prompt)
		free (rl_prompt);
}

/**
 * The function works in a way, that if any of the functions
 * in between fails, an emergency prompt will be printed instead. 
 * This one can be defined in the config.h file. This is why 
 * some things are not protected as it would be expected usually.
 * (e.g. the ft_calloc)
 */
char	*get_input(t_data *data)
{
	char	*input;
	char	*rl_prompt;
	char	*path;
	char	*branch;

	path = NULL;
	branch = NULL;
	if (SHOW_FOLDER)
		path = get_pwd_alloc(true);
	if (SHOW_GIT)
		branch = get_git_alloc();
	rl_prompt = ft_calloc(rl_prompt_len(data, path, branch) + 1, 1);
	add_prompt(data, rl_prompt);
	if (SHOW_FOLDER && path)
		add_folder(rl_prompt, path);
	if (SHOW_GIT && branch)
		add_branch(rl_prompt, branch);
	add_ansi(rl_prompt, RESET);
	if (rl_prompt)
		input = readline(rl_prompt);
	else
		input = readline(EMERGENCY_PROMPT);
	clear_input_func(rl_prompt, path, branch);
	return (input);
}
