/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/01/28 17:18:07 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*input;

	if (SHOW_FOLDER && get_pwd(cwd, true))
		return (NULL);
	if (SHOW_FOLDER && data->exit_status)
		printf("%s%s  %s%s ", FAIL_COLOR, PROMPT, CWD_COLOR, cwd);
	else if (SHOW_FOLDER)
		printf("%s%s  %s%s ", SUCC_COLOR, PROMPT, CWD_COLOR, cwd);
	else if (data->exit_status)
		printf("%s%s  ", FAIL_COLOR, PROMPT);
	else
		printf("%s%s  ", SUCC_COLOR, PROMPT);
	// Add the git thing by checking for the .git folder
	// Branch can be found within ./git/HEAD
	input = readline(RESET);
	return (input);
}
