/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:36:05 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/26 12:44:34 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case_pid(char **word)
{
	char	*res;
	int		pid;

	pid = getpid();
	res = ft_itoa(pid);
	if (!res)
		return (0);
	*word = res;
	return (1);
}

int	check_two_next(char *input, int pos, char value)
{
	int	counter;

	counter = 0;
	while (input[pos] == value)
	{
		pos++;
		counter++;
	}
	if (counter >= 3)
		return (1);
	return (0);
}

int	check_for_triple(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			if (check_two_next(input, i, '>'))
				return (1);
		}
		else if (input[i] == '<')
		{
			if (check_two_next(input, i, '<'))
				return (1);
		}
		i++;
	}
	return (0);
}
