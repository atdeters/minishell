/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 18:41:00 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_data *data, char **env)
{
	data->exit_status = 0;
	data->error = 0;
	data->init_com_fails = 0;
	data->envp = env;
	data->hstlst = NULL;
	data->env_lst = NULL;
	parse_env(data, env);
	load_old_history(HIST_FILE_PATH);
	return (data->error);
}
