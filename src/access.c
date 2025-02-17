/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 17:14:58 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char **command, int *acc_code)
{
	*acc_code = 0;
	if (access(command[0], F_OK) == -1 || !ft_strchr(command[0], '/'))
		*acc_code = p_err_arg(command[0], ERR_ACCESS);
	else if (access(command[0], X_OK) == -1)
		*acc_code = p_err_arg(command[0], ERR_PERM);
	return (*acc_code);
}
