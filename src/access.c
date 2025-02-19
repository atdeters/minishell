/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 17:42:06 by adeters          ###   ########.fr       */
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

int	check_access_files(t_data *data)
{
	int	out_m;
	int	in_m;
	int	error;

	out_m = data->parsed_lst->out_mode;
	in_m = data->parsed_lst->in_mode;
	if (in_m == IN_MODE_FILE)
	{
		error = check_access (data, data->parsed_lst->in, true);
		if (error)
			return (setnret(data, error));
	}
	if (out_m == OUT_MODE_FILE_APP || out_m == OUT_MODE_FILE_TR)
	{
		error = check_access (data, data->parsed_lst->out, true);
		if (error)
			return (setnret(data, error));
	}
	return (0);
}
