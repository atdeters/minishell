/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/01/25 17:34:46 by adeters          ###   ########.fr       */
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
		printf("%s%s  %s%s%s ", FAIL_COLOR, PROMPT, CWD_COLOR, cwd, RESET);
	else if (SHOW_FOLDER)
		printf("%s%s  %s%s%s ", SUCC_COLOR, PROMPT, CWD_COLOR, cwd, RESET);
	else if (data->exit_status)
		printf("%s%s%s  ", FAIL_COLOR, PROMPT, RESET);
	else
		printf("%s%s%s  ", SUCC_COLOR, PROMPT, RESET);
	input = readline(NULL);
	return (input);
}
