/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_biman.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:59:46 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_err_biman_invalid(char **command)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd("biman: ", 2);
	ft_putstr_fd(command[1], 2);
	ft_putstr_fd(" is not an existing builtin function.\n", 2);
	return (ERR_INV_BUILTIN);
}

int	ft_biman(char **command)
{
	if (count_opts(command) != 2)
		return (p_use_biman(), ERR_BUILTIN_USAGE);
	if (!ft_strcmp(command[1], "echo"))
		return (p_use_echo(), 0);
	if (!ft_strcmp(command[1], "cd"))
		return (p_use_cd(), 0);
	if (!ft_strcmp(command[1], "pwd"))
		return (p_use_pwd(), 0);
	if (!ft_strcmp(command[1], "export"))
		return (p_use_export(), 0);
	if (!ft_strcmp(command[1], "unset"))
		return (p_use_unset(), 0);
	if (!ft_strcmp(command[1], "env"))
		return (p_use_env(), 0);
	if (!ft_strcmp(command[1], "exit"))
		return (p_use_exit(), 0);
	if (!ft_strcmp(command[1], "alias"))
		return (p_use_alias(), 0);
	if (!ft_strcmp(command[1], "biman"))
		return (p_use_biman(), 0);
	return (p_err_biman_invalid(command));
}
