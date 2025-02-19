/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 15:43:14 by vsenniko         ###   ########.fr       */
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

int	pnc_err(t_data *data)
{
	data->init_com_fails++;
	ft_fprintf(2, "%s ", VASH_ERR_IDENT);
	if (data->error == ERR_PIPE)
		ft_fprintf(2, "%s", E_NC_MSG_FUNC_PIPE);
	if (data->error == ERR_SPLIT)
		ft_fprintf(2, "%s", E_NC_MSG_SPLIT);
	ft_fprintf(2, " [%d]\n", data->init_com_fails);
	return (data->error);
}

int	p_err_arg(int code, const char *arg)
{
	ft_fprintf(2, "%s ", VASH_ERR_IDENT);
	if (code == ERR_ACCESS)
		ft_fprintf(2, "%s%s\n", E_NC_MSG_ACCESS, arg);
	if (code == ERR_PERM)
		ft_fprintf(2, "%s%s\n", E_NC_MSG_PERM, arg);
	if (code == ERR_OPEN)
		ft_fprintf(2, "%s%s\n", E_NC_MSG_OPEN, arg);
	return (code);
}
