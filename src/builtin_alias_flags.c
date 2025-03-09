/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:42:22 by andreas           #+#    #+#             */
/*   Updated: 2025/03/09 12:49:03 by andreas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_flag_help_alias(char **command)
{
	if (count_opts(command) != 2)
		return (false);
	if (!ft_strcmp(command[1], "--help"))
		return (true);
	if (!ft_strcmp(command[1], "-h"))
		return (true);
	return (false);
}

bool	has_flag_rm_alias(char **command)
{
	if (count_opts(command) != 3)
		return (false);
	if (!ft_strcmp(command[1], "-r"))
		return (true);
	if (!ft_strcmp(command[1], "--remove"))
		return (true);
	return (false);
}
