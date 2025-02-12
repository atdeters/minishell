/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/02/12 19:42:49 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_err(int code)
{
	if (code == INIT_PROG)
		ft_fprintf(2, "minishell failed to initialize\n");
	if (code == INIT_COM)
		ft_fprintf(2, "command failed to initialize\n");
	if (code == EXEC)
		ft_fprintf(2, "execve failed to execute\n");
	if (code == DUP)
		ft_fprintf(2, "dup2 failed to execute\n");
	if (code == FORK)
		ft_fprintf(2, "fork failed to execute\n");
	if (code == VASH_E)
		ft_fprintf(2, "command initialization failed too often\n");
	return (code);
}

void	p_vash_err(t_data *data, char *arg)
{
	data->init_com_fails++;
	ft_fprintf(2, "vash: ");
	if (data->error == PIPE_E)
	{
		ft_fprintf(2, "pipe: pipe could temporarily not be built [%d]\n",
			data->init_com_fails);
	}
}
