/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/02/13 17:37:30 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_err(int code)
{
	ft_fprintf(2, "%s ", VASH_ERR_IDENT);
	if (code == INIT_PROG)
		ft_fprintf(2, "%s\n", E_MSG_INIT_PROG);
	if (code == INIT_COM)
		ft_fprintf(2, "%s\n", E_MSG_INIT_COM);
	if (code == EXEC)
		ft_fprintf(2, "%s\n", E_MSG_FUNC_EXECVE);
	if (code == DUP)
		ft_fprintf(2, "%s\n", E_MSG_FUNC_DUP2);
	if (code == FORK)
		ft_fprintf(2, "%s\n", E_MSG_FUNC_FORK);
	return (code);
}

void	p_nc_err(t_data *data, char *arg)
{
	data->init_com_fails++;
	ft_fprintf(2, "%s ", VASH_ERR_IDENT);
	if (data->error == PIPE_E)
		ft_fprintf(2, "%s [%d]\n", E_MSG_FUNC_PIPE, data->init_com_fails);
}
