/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 20:29:54 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *data)
{
	char	*input;
	char	rl_prompt[PATH_MAX + RL_PROMPT_MAX];

	ft_bzero(rl_prompt, sizeof(rl_prompt));
	add_prompt(data, rl_prompt);
	if (SHOW_FOLDER)
		add_folder(rl_prompt);
	if (SHOW_GIT)
		add_git(rl_prompt);
	add_ansi(rl_prompt, RESET);
	input = readline(rl_prompt);
	return (input);
}
