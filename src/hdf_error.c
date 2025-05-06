/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:03:24 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_hdf_int_warn(char *delimiter)
{
	ft_putstr_fd(SHELL_ERR_IDENT, 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted \'", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("\')\n", 2);
}
