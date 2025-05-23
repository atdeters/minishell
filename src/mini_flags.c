/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:51:33 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_flag_single(char *flag)
{
	int	i;

	if (!ft_strcmp(flag, "--single"))
		return (true);
	if (!ft_strcmp(flag, "-s"))
		return (true);
	i = 1;
	if (flag[0] != '-')
		return (false);
	while (flag[i])
	{
		if (flag[i] != 's')
			return (false);
		i++;
	}
	return (true);
}

bool	is_flag_help(char *flag)
{
	int	i;

	if (!ft_strcmp(flag, "--help"))
		return (true);
	if (!ft_strcmp(flag, "-h"))
		return (true);
	i = 1;
	if (flag[0] != '-')
		return (false);
	while (flag[i])
	{
		if (flag[i] != 'h')
			return (false);
		i++;
	}
	return (true);
}

int	check_flags(t_data *data, int ac, char **av)
{
	if (ac == 3 && is_flag_single(av[1]))
		data->flag_single = true;
	else if (ac == 3)
		rage_quit(data, ERR_USAGE, true, NULL);
	else
		data->flag_single = false;
	if (ac == 2 && is_flag_help(av[1]))
	{
		p_use_msh();
		rage_quit(data, 0, true, NULL);
	}
	else if (ac == 2)
		rage_quit(data, ERR_USAGE, true, NULL);
	return (0);
}
