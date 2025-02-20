/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 21:14:44 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		rl_prompt_len(t_data *data, char *path, char *branch);
void	clear_input_func(char *rl_prompt, char *path, char *branch);

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
	if (!input)
		exit(1);
	clear_input_func(rl_prompt, path, branch);
	return (input);
}

/**
 * @brief Calculates the total length required for the `rl_prompt`,
 * including ANSI escape sequences.
 * 
 * This function computes the length of the prompt by considering dynamic
 * components like the exit status, current directory path, and git branch.
 * It also includes the necessary space for ANSI escape sequences and their
 * ANSI_SHELL (aka `\001` and `\002`) to ensure proper formatting.
 * The length calculation accounts for whether certain components
 * (like exit  status, folder, or git branch) are enabled.
 * 
 * @param data A pointer to the `t_data` structure,
 * containing the exit status.
 * @param path The current directory path
 * (included if `SHOW_FOLDER` is enabled).
 * @param branch The current Git branch name
 * (included if `SHOW_GIT` is enabled).
 * 
 * @return The total length (in characters) of the prompt, including all
 * elements and formatting.
 * 
 * @note This function ensures that the length is correctly calculated,
 * even if some elements are not present. ANSI escape sequences are 
 * properly accounted for to avoid rendering issues.
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
