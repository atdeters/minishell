/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:25:57 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/21 16:29:09 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_problen(t_data *data)
{
	int sing;
	int dob;
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
		return(data->error = ERR_PARS_SINGLE_QUTE, 1);
	if (dob % 2 != 0)
		return(data->error = ERR_PARS_DOUBLE_QUTE, 1);
	return (0);
}
