/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rage_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:49:34 by adeters           #+#    #+#             */
/*   Updated: 2025/03/06 14:53:26 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rage_quit(t_data *data, int exit_code, bool write_hist, char *err_cmd)
{
	if (err_cmd && exit_code && data->p_err)
		p_err_arg(exit_code, err_cmd);
	else if (exit_code && data->p_err)
		p_err(exit_code);
	if (write_hist)
		write_hst_file(data, data->hist_path);
	else
		free_hst_list(data);
	free_all_com(data);
	free_all_global(data);
	data->exit_status = exit_code;
	exit (exit_code);
}
