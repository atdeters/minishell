/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/03/03 16:23:39 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path_for_file(t_data *data, char *file_name)
{
	t_env_lst	*tmp;
	char		*address;
	char		*tmp_ad;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->filed))
		{
			tmp_ad = ft_strjoin(tmp->value, "/");
			if (!tmp_ad)
				return (data->error = ERR_MALLOC, NULL);
			address = ft_strjoin(tmp_ad, file_name);
			if (!address)
				return (free(tmp_ad), data->error = ERR_MALLOC, NULL);
			return (free(tmp_ad), address);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_shlvl(t_data *data, t_env_lst **lst)
{
	t_env_lst	*tmp;
	int			lvl;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp("SHLVL", tmp->filed))
		{
			lvl = ft_atoi(tmp->value) + 1;
			free (tmp->value);
			tmp->value = ft_itoa(lvl);
			if (!tmp->value)
				rage_quit(data, ERR_MALLOC, true, NULL);
			
		}
		tmp = tmp->next;
	}
}

int	init_shell(t_data *data, int ac, char **av, char **env)
{
	if (ac != 1 && ac != 3 && ac != 2)
		exit(pc_err(ERR_USAGE));
	*data = (t_data){0};
	check_flags(data, ac, av);
	parse_env(data, env);
	set_shlvl(data, &data->env_lst);
	parser_env_into_arr(data);
	data->alias_path = get_home_path_for_file(data, ALIAS_FILE_NAME);
	if (!data->alias_path)
		rage_quit(data, data->error, false, NULL);
	load_alias_lst(data, data->alias_path);
	data->hist_path = get_home_path_for_file(data, HIST_FILE_NAME);
	if (!data->hist_path)
		rage_quit(data, data->error, false, NULL);
	load_old_history(data->hist_path);
	return (0);
}
