/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:37 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 16:54:59 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *data)
{
	char	*input;

	p_prompt(data);
	if (SHOW_FOLDER)
		p_folder();
	if (SHOW_GIT)
		p_git();
	input = readline(RESET);
	return (input);
}
