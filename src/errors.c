/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 17:44:57 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setnret(t_data *data, int code)
{
	data->error = code;
	return (code);
}

int	p_err(int code)
{
	if (code == ERR_INIT_PROG)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_INIT_PROG);
	if (code == ERR_INIT_COM)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_INIT_COM);
	if (code == ERR_EXECVE)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_FUNC_EXECVE);
	if (code == ERR_DUP2)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_FUNC_DUP2);
	if (code == ERR_FORK)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_FUNC_FORK);
	if (code == ERR_USAGE)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_USAGE);
	if (code == ERR_PIPE)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_NC_MSG_FUNC_PIPE);
	if (code == ERR_PARS)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_PARSING);
	if (code == ERR_PARS_SINGLE_QUTE)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_SINGLE_QOUTE);
	if (code == ERR_PARS_DOUBLE_QUTE)
		ft_fprintf(2, "%s %s\n", VASH_ERR_IDENT, E_MSG_DOUBLE_QOUTE);
	return (code);
}

int	p_err_arg(int code, const char *arg)
{
	if (code == ERR_ACCESS)
		ft_fprintf(2, "%s %s%s\n", VASH_ERR_IDENT, E_NC_MSG_ACCESS, arg);
	if (code == ERR_ACCESS_FILE)
		ft_fprintf(2, "%s %s: %s\n", VASH_ERR_IDENT, arg, ERR_MSG_ACCESS_FILE);
	if (code == ERR_PERM)
		ft_fprintf(2, "%s %s%s\n", VASH_ERR_IDENT, E_NC_MSG_PERM, arg);
	if (code == ERR_OPEN)
		ft_fprintf(2, "%s %s%s\n", VASH_ERR_IDENT, E_NC_MSG_OPEN, arg);
	return (code);
}
