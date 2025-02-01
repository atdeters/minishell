/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ansi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:10:17 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 20:22:14 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_ansi(char *rl_prompt, char *color)
{
	ft_strcpy(rl_prompt, "\001");
	ft_strcat(rl_prompt, color);
	ft_strcat(rl_prompt, "\002");
}

void	add_ansi(char *rl_prompt, char *color)
{
	ft_strcat(rl_prompt, "\001");
	ft_strcat(rl_prompt, color);
	ft_strcat(rl_prompt, "\002");
}
