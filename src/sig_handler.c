/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:32 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/25 19:59:06 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Work only on standart mode
// Should handle here_doc and execution mode

void	sig_handle_here_doc(int signum)
{
	t_data	*data;
	char	nl;

	nl = '\n';
	data = pointer_to_data(NULL);
	if (signum == SIGINT)
	{
		g_signal = signum;
		rl_on_new_line();
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, &nl);
	}
}

void	sig_handle_basic(int signum)
{
	t_data	*data;

	data = pointer_to_data(NULL);
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free_all_com(data);
	}
}

t_data	*pointer_to_data(t_data *data)
{
	static t_data	*pointer;

	if (data)
		pointer = data;
	return (pointer);
}
