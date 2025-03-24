/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:38:57 by andreas           #+#    #+#             */
/*   Updated: 2025/03/24 15:48:08 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	input_is_yes(char *input)
{
	if (!ft_strcmp(input, "yes\n"))
		return (true);
	if (!ft_strcmp(input, "Yes\n"))
		return (true);
	if (!ft_strcmp(input, "y\n"))
		return (true);
	if (!ft_strcmp(input, "Y\n"))
		return (true);
	return (false);
}

bool	input_is_no(char *input)
{
	if (!ft_strcmp(input, "no\n"))
		return (true);
	if (!ft_strcmp(input, "No\n"))
		return (true);
	if (!ft_strcmp(input, "n\n"))
		return (true);
	if (!ft_strcmp(input, "N\n"))
		return (true);
	return (false);
}

bool	user_agrees(t_data *data)
{
	char	*line;

	line = get_next_line(0);
	if (!line)
		rage_quit(data, ERR_MALLOC, true, NULL);
	while (line)
	{
		if (input_is_yes(line))
			return (get_next_line(-1), free(line), true);
		if (input_is_no(line))
			return (get_next_line(-1), free(line), false);
		ft_putstr_fd("Invalid input. Please enter Y or n ", 2);
		free(line);
		line = get_next_line(0);
		if (!line)
		{
			get_next_line(-1);
			rage_quit(data, ERR_MALLOC, true, NULL);
		}
	}
	return (free(line), get_next_line(-1), false);
}
