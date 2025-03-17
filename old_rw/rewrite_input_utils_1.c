/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:25:57 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/17 19:58:52 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_problem(t_data *data)
{
	int	sing;
	int	dob;
	int	i;

	i = 0;
	sing = 0;
	dob = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'')
			sing++;
		else if (data->input[i] == '"')
			dob++;
		i++;
	}
	if (sing % 2 != 0)
		return (setnret(data, ERR_PARS_SINGLE_QUTE));
	if (dob % 2 != 0)
		return (setnret(data, ERR_PARS_DOUBLE_QUTE));
	return (0);
}

int	in_single_qoute(t_data *data, int pos)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (i != pos)
	{
		if (data->input[i] == '\'')
			counter++;
		i++;
	}
	if (counter % 2 != 0)
		return (1);
	return (0);
}

int	pipe_problem(t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (data->input[i])
	{
		if (data->input[i] == '|')
			flag = 1;
		if (ft_isalnum(data->input[i]))
			flag = 0;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}
