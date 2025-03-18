/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:57:21 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 14:46:42 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **command)
{
	if (has_flag_help_alias(command))
		return (print_usage(data, ENV_HELP_FILE_PATH), 0);
	else if (command[1])
		return (print_usage(data, ENV_HELP_FILE_PATH), ERR_ENV_USAGE);
	return (print_env_lst(data->env_lst, false), 0);
}
