/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 15:11:40 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(t_data *data, char *name, bool is_file)
{
	int	error;

	error = 0;
	if (access(name, F_OK) == -1)
		error = p_err_arg(ERR_ACCESS, name);
	else if (!is_file && access(name, X_OK) == -1)
		error = p_err_arg(ERR_PERM, name);
	else if (is_file && access(name, R_OK) == -1)
		error = p_err_arg(ERR_PERM, name);
	else if (!is_file && !ft_strchr(name, '/'))
		error = p_err_arg(ERR_ACCESS, name);
	if (error)
		return (setnret(data, error));
	return (0);
}
