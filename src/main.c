/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/01/29 14:14:14 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;

	if (init_shell(&data))
		return (p_err(INIT));
	
	while (true)
	{
		data.input = get_input(&data);
		// Should use vova's prompt (because stuff like "cl"ea"r")
		if (!ft_strncmp(data.input, "clear", 5))
			clear();
		free(data.input);
	}
}
