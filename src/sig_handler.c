/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:32 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/04 17:16:01 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle_here_doc(int signum)
{
	char	nl;

	nl = '\n';
	g_signal = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, &nl);
}

void	sig_handle_basic(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
