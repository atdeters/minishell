/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:45:30 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 20:24:12 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cool_dup(int fd_in, int fd_out)
{
	if (fd_in != 0 && dup2(fd_in, STDIN_FILENO) == -1)
		return (1);
	if (fd_out != 1 && dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);
	if (fd_in != -1 && fd_in != STDIN_FILENO)
		close (fd_in);
	if (fd_out != -1 && fd_out != STDOUT_FILENO)
		close (fd_out);
	return (0);
}
