/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setnret(t_data *data, int code)
{
	data->error = code;
	return (code);
}

void	p_err_formatted(char *msg)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd(msg, 2);
}

void	p_err_arg_formatted(char *msg, char *arg)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd("\n", 2);
}

int	p_err(int code)
{
	if (code == ERR_USAGE)
		p_use_msh();
	if (code == ERR_EXECVE)
		p_err_formatted(ERR_MSG_FUNC_EXECVE);
	if (code == ERR_DUP2)
		p_err_formatted(ERR_MSG_FUNC_DUP2);
	if (code == ERR_FORK)
		p_err_formatted(ERR_MSG_FUNC_FORK);
	if (code == ERR_PIPE)
		p_err_formatted(ERR_MSG_FUNC_PIPE);
	if (code == ERR_CHDIR)
		p_err_formatted(ERR_MSG_FUNC_CHDIR);
	if (code == ERR_GETCWD)
		p_err_formatted(ERR_MSG_FUNC_GETCWD);
	if (code == ERR_PARS)
		p_err_formatted(ERR_MSG_PARSING);
	if (code == ERR_INVALID_REDIR)
		p_err_formatted(ERR_MSG_INVALID_REDIR);
	if (code == ERR_PARS_SINGLE_QUTE)
		p_err_formatted(ERR_MSG_SINGLE_QOUTE);
	if (code == ERR_PARS_DOUBLE_QUTE)
		p_err_formatted(ERR_MSG_DOUBLE_QOUTE);
	return (code);
}

int	p_err_arg(int code, char *arg)
{
	if (code == ERR_ACCESS)
		p_err_arg_formatted(ERR_MSG_ACCESS, arg);
	if (code == ERR_NOTDIR)
		p_err_arg_formatted(ERR_MSG_NOTDIR, arg);
	if (code == ERR_ACCESS_FILE)
		p_err_arg_formatted(ERR_MSG_ACCESS_FILE, arg);
	if (code == ERR_PERM)
		p_err_arg_formatted(ERR_MSG_PERM, arg);
	if (code == ERR_OPEN)
		p_err_arg_formatted(ERR_MSG_OPEN, arg);
	if (code == ERR_INVALID_PATH)
		p_err_arg_formatted(ERR_MSG_INVALID_PATH, arg);
	if (code == ERR_DIR)
		p_err_arg_formatted(ERR_MSG_DIR, arg);
	if (code == ERR_VALID_IDENT)
		p_err_arg_formatted(ERR_MSG_VALID_IDENT, arg);
	return (code);
}
