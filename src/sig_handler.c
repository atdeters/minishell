/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:32 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/19 14:22:49 by adeters          ###   ########.fr       */
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
		get_next_line(-1);
		ft_printf("\n");
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
