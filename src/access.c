/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 16:17:10 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char **command, int *acc_code)
{
	*acc_code = 0;
	if (access(command[0], F_OK) == -1 || !ft_strchr(command[0], '/'))
		*acc_code = p_err_arg(ERR_ACCESS, command[0]);
	else if (access(command[0], X_OK) == -1)
		*acc_code = p_err_arg(ERR_PERM, command[0]);
	return (*acc_code);
}
