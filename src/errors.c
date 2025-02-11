/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:01:48 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 20:34:02 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_err(int code)
{
	if (code == INIT_PROG)
		ft_fprintf(2, "minishell failed to initialize\n");
	if (code == INIT_COM)
		ft_fprintf(2, "command failed to initialize\n");
	return (code);
}
