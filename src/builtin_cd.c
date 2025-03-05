/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:31:37 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 20:05:20 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_cd(char **command)
{
	// Needs a lot more shit etc.
	// Give the below a home adress instead of the ".."
	// if (!command[1] && chdir("..") == -1)
	// 	return (1);
	if (chdir(command[1]) == -1)
		return (1);
	return (0);
}
