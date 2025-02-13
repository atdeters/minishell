/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/02/13 17:53:49 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setnret(t_data *data, int code)
{
	data->error = code;
	return (code);
}

int	pc_err(int code)
{
	ft_fprintf(2, "%s ", VASH_ERR_IDENT);
	if (code == ERR_INIT_PROG)
		ft_fprintf(2, "%s\n", E_MSG_INIT_PROG);
	if (code == ERR_INIT_COM)
		ft_fprintf(2, "%s\n", E_MSG_INIT_COM);
	if (code == ERR_EXECVE)
		ft_fprintf(2, "%s\n", E_MSG_FUNC_EXECVE);
	if (code == ERR_DUP2)
		ft_fprintf(2, "%s\n", E_MSG_FUNC_DUP2);
	if (code == ERR_FORK)
		ft_fprintf(2, "%s\n", E_MSG_FUNC_FORK);
	return (code);
}

void	pnc_err(t_data *data)
{
	data->init_com_fails++;
	ft_fprintf(2, "%s ", VASH_ERR_IDENT);
	if (data->error == ERR_PIPE)
		ft_fprintf(2, "%s", E_NC_MSG_FUNC_PIPE);
	ft_fprintf(2, " [%d]\n", data->init_com_fails);
}
