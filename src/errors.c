/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/03/25 14:07:19 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
}

int	p_err(t_data *data, int code)
{
	if (code == ERR_USAGE)
		print_usage(data, HELP_FILE_PATH);
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
		if (code == ERR_ACCESS_FILE)
			p_err_arg_formatted(arg, ERR_MSG_ACCESS_FILE);
		if (code == ERR_PERM)
			p_err_arg_formatted(ERR_MSG_PERM, arg);
		if (code == ERR_OPEN)
			p_err_arg_formatted(ERR_MSG_OPEN, arg);
		if (code == ERR_INVALID_PATH)
			p_err_arg_formatted(ERR_MSG_INVALID_PATH, arg);
	return (code);
}
