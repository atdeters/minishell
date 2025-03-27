/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:57:21 by adeters           #+#    #+#             */
/*   Updated: 2025/03/18 15:24:16 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **command)
{
	if (command[1])
		return (p_use_env(), ERR_BUILTIN_USAGE);
	return (print_env_lst(data->env_lst, false), 0);
}
