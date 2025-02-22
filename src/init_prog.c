/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 21:50:55 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hist_file_path(t_data *data)
{
	t_env_lst	*tmp;
	char		*address;
	char		*tmp_ad;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strncmp("HOME", tmp->filed,
				ft_strlen(tmp->filed)))
		{
			tmp_ad = ft_strjoin(tmp->value, "/");
			if (!tmp_ad)
				return (data->error = ERR_MALLOC, NULL);
			address = ft_strjoin(tmp_ad, HIST_FILE_NAME);
			if (!address)
				return (free(tmp_ad), data->error = ERR_MALLOC, NULL);
			return (free(tmp_ad), address);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	init_shell(t_data *data, int ac, char **av, char **env)
{
	if (ac != 1 && ac != 3 && ac != 2)
		return (pc_err(ERR_USAGE));
	*data = (t_data){0};
	data->on = true;
	if (check_flags(data, ac, av))
		return (data->error);
	parse_env(data, env);
	parser_env_into_arr(data);
	data->hist_path = get_hist_file_path(data);
	if (!data->hist_path)
		rage_quit(data, data->error);
	load_old_history(data->hist_path);
	return (data->error);
}
