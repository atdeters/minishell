/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:25:57 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/25 18:36:46 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	else_if_for_loop(char ch, int *flag, int *sing, int *dob)
{
	if ((ch == '\'' && *flag == 1) || (ch == '"' && *flag == 2))
	{
		if (*flag == 1)
			(*sing)++;
		else
			(*dob)++;
		*flag = 0;
	}
}

static void	loop_for_quotes(t_data *data, int *flag, int *sing, int *dob)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'' && *flag == 0)
		{
			*flag = 1;
			(*sing)++;
		}
		else if (data->input[i] == '"' && *flag == 0)
		{
			*flag = 2;
			(*dob)++;
		}
		else
			else_if_for_loop(data->input[i], flag, sing, dob);
		i++;
	}
}

int	quotes_problem(t_data *data)
{
	int	sing;
	int	dob;
	int	flag;

	sing = 0;
	dob = 0;
	flag = 0;
	loop_for_quotes(data, &flag, &sing, &dob);
	if (sing % 2 != 0)
		return (setnret(data, ERR_PARS_SINGLE_QUTE));
	if (dob % 2 != 0)
		return (setnret(data, ERR_PARS_DOUBLE_QUTE));
	return (0);
}

int	in_single_qoute(int pos, char *input)
{
	int	i;
	int	counter;
	int	flag;

	counter = 0;
	i = 0;
	flag = 0;
	while (i != pos)
	{
		if (input[i] == '"' && flag == 0)
			flag = 2;
		else if (input[i] == '"' && flag == 2)
			flag = 0;
		if (input[i] == '\'' && !flag)
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
	flag = 0;
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
