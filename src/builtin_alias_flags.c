/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:42:22 by andreas           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	has_flag_rm_alias(char **command)
{
	int	i;

	if (count_opts(command) != 3)
		return (false);
	if (!ft_strcmp(command[1], "--remove"))
		return (true);
	if (command[1][0] == '-')
	{
		i = 1;
		while (command[1][i])
		{
			if (command[1][i] != 'r')
				return (false);
			i++;
		}
	}
	else
		return (false);
	return (true);
}
