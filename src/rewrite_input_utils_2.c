/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:36:05 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/25 18:36:23 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case_pid(char **word)
{
	char	*res;
	int		pid;

	pid = getpid();
	res = ft_itoa(pid);
	if (!res)
		return (0);
	*word = res;
	return (1);
}
