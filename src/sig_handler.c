/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:32 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/25 17:34:53 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Work only on standart mode
// Should handle here_doc and execution mode

void	signal_handler(int signum)
{
	t_data	*data;

	data = pointer_to_data(NULL);
	if (signum == SIGINT)
	{
		// g_signal = SIGINT;
		// if (!data->stage_flag)
		// 	return ;
		// write(STDOUT_FILENO, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// free_all_com(data);
		// ft_printf("signal recived, value updated\n");

		g_signal = signum;
		write(0, "\n", 1);
	}
}

t_data	*pointer_to_data(t_data *data)
{
	static t_data	*pointer;

	if (data)
		pointer = data;
	return (pointer);
}
