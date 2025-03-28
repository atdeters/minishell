/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:58:19 by adeters           #+#    #+#             */
/*   Updated: 2025/03/28 19:02:04 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_com(t_data *data)
{
	while (data->parsed_lst && data->parsed_lst->prev)
		data->parsed_lst = data->parsed_lst->prev;
	if (data->flag_single == false)
		cool_free(&data->input);
	if (data->parsed_lst)
		free_p_lst(&data->parsed_lst);
	if (data->token_lst)
		ft_token_lstclear(&data->token_lst);
	if (data->hdf_arr)
		free_hdf_arr(data);
	if (data->prog_path)
		cool_free(&data->prog_path);
	close_all(data);
}

void	free_all_global(t_data *data)
{
	cool_free(&data->hist_path);
	cool_free(&data->alias_path);
	cool_free(&data->home_path);
	if (data->envp)
		fr_lst(data->envp);
	if (data->alias_lst)
		ft_env_lstclear(&data->alias_lst);
	if (data->env_lst)
		ft_env_lstclear(&data->env_lst);
}
