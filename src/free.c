/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:00:46 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 17:49:48 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fr_lst(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	close_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipes_amount)
	{
		if (data->fd_pipe[i][0] != -1)
			close (data->fd_pipe[i][0]);
		if (data->fd_pipe[i][1] != -1)
			close (data->fd_pipe[i][1]);
		i++;
	}
}

void	free_hdf_arr(t_data *data)
{
	int	i;

	i = 0;
	while (data->hdf_arr && data->hdf_arr[i])
	{
		unlink(data->hdf_arr[i]);
		free (data->hdf_arr[i]);
		data->hdf_arr[i] = NULL;
		i++;
	}
	free(data->hdf_arr);
	data->hdf_arr = NULL;
}

void	free_all_com(t_data *data)
{
	if (data->input && data->flag_single == false)
		free (data->input);
	while (data->parsed_lst && data->parsed_lst->prev)
		data->parsed_lst = data->parsed_lst->prev;
	if (data->parsed_lst)
		free_p_lst(&data->parsed_lst);
	if (data->token_lst)
		ft_token_lstclear(&data->token_lst);
	if (data->hdf_arr)
		free_hdf_arr(data);
	close_all(data);
}

void	free_all_global(t_data *data)
{
	if (data->hist_path)
		free (data->hist_path);
	if (data->alias_path)
		free (data->alias_path);
	if (data->envp)
		fr_lst(data->envp);
	if (data->home_path)
		free (data->home_path);
	if (data->msh_path)
		free (data->msh_path);
	if (data->alias_lst)
		ft_env_lstclear(&data->alias_lst);
	if (data->env_lst)
		ft_env_lstclear(&data->env_lst);
}
