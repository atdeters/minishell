/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:57:21 by adeters           #+#    #+#             */
/*   Updated: 2025/03/17 19:08:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Not fully correct (doesn't include newly added stuff)
void	ft_env(t_data *data)
{
	print_env_lst(data->env_lst);
}
