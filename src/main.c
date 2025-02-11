/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 14:06:54 by vsenniko         ###   ########.fr       */
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
		if (data.input && !ft_strncmp(data.input, "clear", 5))
			clear();
		else if (data.input && !ft_strncmp(data.input, "pwd", 3))
			pwd();
		free(data.input);
	}
}
