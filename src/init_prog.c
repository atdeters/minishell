/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/12 18:45:43 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initializing the whole shell program before first command
int	init_shell(t_data *data, char **env)
{
	data->exit_status = 0;
	data->error = 0;
	data->env_lst = NULL;
	data->envp = env;
	return (data->error);
}
