/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:32 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/17 19:02:37 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	t_data	*data;

	data = pointer_to_data(NULL);
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free_all_com(data);
	}
	else if (signum == SIGQUIT)
	{
		// what shoulf I do? Should I display it?  or what?
	}
}

t_data	*pointer_to_data(t_data *data)
{
	static t_data *pointer;

	if (data)
		pointer = data;
	return (pointer);
}