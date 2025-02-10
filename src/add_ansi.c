/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ansi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:10:17 by adeters           #+#    #+#             */
/*   Updated: 2025/02/10 18:21:50 by adeters          ###   ########.fr       */
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
