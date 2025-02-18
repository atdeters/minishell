/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 16:07:52 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(t_data *data, char **command, int *acc_code)
{
	*acc_code = 0;
	if (access(command[0], F_OK) == -1 || !ft_strchr(command[0], '/'))
		*acc_code = p_err_arg(data, ERR_ACCESS);
	else if (access(command[0], X_OK) == -1)
		*acc_code = p_err_arg(data, ERR_PERM);
	return (*acc_code);
}
