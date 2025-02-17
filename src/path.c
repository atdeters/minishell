/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:52:51 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 15:00:49 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_isdirect(char **command)
{
	if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		return (0);
	else if (access(command[0], F_OK) == 0 && access(command[0], X_OK) != 0)
		return (126);
	return (1);
}

int	exe_isinpath(char **command, char *path)
{
	
}