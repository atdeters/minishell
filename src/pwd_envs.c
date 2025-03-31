/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:21:33 by adeters           #+#    #+#             */
/*   Updated: 2025/03/31 20:25:35 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Automatically frees entry in the process!
 */
int	set_pwd_envs(t_data *data, char *entry)
{
	int		j;
	char	*tmp;

	j = 0;
	while (entry[j])
	{
		if (entry[j] == '=')
		{
			tmp = ft_substr(entry, 0, j);
			if (!tmp)
				return (free(entry), 1);
			remove_env_node(&data->env_lst, tmp);
			free(tmp);
			transfer_into_node(entry, data, j);
			break ;
		}
		j++;
	}
	return (free(entry), 0);
}

void	replace_oldpwd_env(t_data *data, char *oldpwd)
{
	t_env_lst	*tmp;
	char		*tmp_pwd;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->filed, "OLDPWD"))
		{
			free (tmp->value);
			tmp->value = ft_strdup(oldpwd);
			if (!tmp->value)
				rage_quit(data, ERR_MALLOC, true, NULL);
			return ;
		}
		tmp = tmp->next;
	}
	tmp_pwd = ft_strjoin("OLDPWD=", oldpwd);
	if (!tmp_pwd)
		rage_quit(data, ERR_MALLOC, true, NULL);
	if (set_pwd_envs(data, tmp_pwd))
		rage_quit(data, ERR_MALLOC, true, NULL);
}

void	replace_pwd_env(t_data *data)
{
	t_env_lst	*tmp;
	char		*tmp_pwd;
	char		*entry;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->filed, "PWD"))
		{
			replace_oldpwd_env(data, tmp->value);
			free (tmp->value);
			tmp->value = get_pwd_alloc(data, false);
			return ;
		}
		tmp = tmp->next;
	}
	tmp_pwd = get_pwd_alloc(data, false);
	entry = ft_strjoin("PWD=", tmp_pwd);
	free (tmp_pwd);
	if (!entry)
		rage_quit(data, ERR_MALLOC, true, NULL);
	if (set_pwd_envs(data, entry))
		rage_quit(data, ERR_MALLOC, true, NULL);
}
