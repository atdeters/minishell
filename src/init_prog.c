/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 18:15:18 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag_single(char *flag)
{
	int	i;

	if (!ft_strncmp(flag, "--single", ft_strlen(flag)))
		return (true);
	if (!ft_strncmp(flag, "-s", ft_strlen(flag)))
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

void	check_flags(t_data *data, int ac, char **av)
{
	data->flag_single_switch = true;
	if (ac == 3 && is_flag_single(av[1]))
		data->flag_single = true;
	else
		data->flag_single = false;
}


int	init_shell(t_data *data, int ac, char **av, char **env)
{
	
	// Check usage
	if (ac != 1 && (ac != 3))
		return (pc_err(ERR_USAGE));
	*data = (t_data){0};
	// Check flags

	check_flags(data, ac, av);


	// data->exit_status = 0;
	// data->error = 0;
	// data->hstlst = NULL;
	// data->env_lst = NULL;
	parse_env(data, env);
	parser_env_into_arr(data);
	load_old_history(HIST_FILE_PATH);
	return (data->error);
}
