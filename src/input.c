/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/01/30 16:25:20 by adeters          ###   ########.fr       */
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

char	*get_input(t_data *data)
{
	char	*input;

	p_prompt(data);
	if (SHOW_FOLDER && p_folder())
		return (NULL);
	input = readline(RESET);
	return (input);
}
