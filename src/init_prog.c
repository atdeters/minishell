/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/03/25 16:50:01 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

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

void	set_home_path(t_data *data)
{
	t_env_lst	*tmp;
	char		*path;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->filed))
		{
			path = ft_strdup(tmp->value);
			if (!path)
				rage_quit(data, ERR_MALLOC, true, NULL);
			data->home_path = path;
			return ;
		}
		tmp = tmp->next;
	}
	data->home_path = NULL;
	return ;
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
	g_signal = 0;
	if (ac != 1 && ac != 3 && ac != 2)
		exit(p_err(ERR_USAGE));
	*data = (t_data){0};
	data->p_err = true;
	data->msh_path = get_pwd_alloc(data, false);
	check_flags(data, ac, av);
	parse_env(data, env);
	set_shlvl(data, &data->env_lst);
	set_home_path(data);
	data->alias_path = get_home_path_for_file(data, ALIAS_FILE_NAME);
	if (!data->alias_path)
		rage_quit(data, data->error, false, NULL);
	load_alias_lst(data, data->alias_path);
	data->hist_path = get_home_path_for_file(data, HIST_FILE_NAME);
	if (!data->hist_path)
		rage_quit(data, data->error, false, NULL);
	load_old_history(data->hist_path);
	data->stage_flag = 0;
	return (0);
}
