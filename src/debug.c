/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:08:41 by adeters           #+#    #+#             */
/*   Updated: 2025/03/06 16:17:44 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chp(void)
{
	static int	pos;

	printf("Checkpoint %d successful!\n", pos);
	pos++;
}

void	print_parsed_data(t_parsed *lst)
{
	int	i;

	i = 0;
	while (lst->cmd_and_args[i])
	{
		printf("cmd_and_args[%d]: %s\n", i, lst->cmd_and_args[i]);
		i++;
	}
	printf("cmd_and_args[%d] = %s\n", i, lst->cmd_and_args[i]);
	printf("in_mode: %d\n", lst->in_mode);
	printf("out_mode: %d\n", lst->out_mode);
}

void	p_err_src(char *file, int line)
{
	ft_putstr_fd("source: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" line: ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}
