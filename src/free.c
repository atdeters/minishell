/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:00:46 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 19:06:39 by adeters          ###   ########.fr       */
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

// Supposed to free everything that can be allocated
void	rage_quit(t_data *data, int exit_code)
{
	write_hst_file(data, HIST_FILE_PATH);
	if (data->input && data->flag_single == false)
		free (data->input);
	if (data->prompt)
		free (data->prompt);
	if (data->env_lst)
		ft_env_lstclear(&data->env_lst);
	if (data->parsed_lst)
		free_p_lst(&data->parsed_lst);
	if (data->token_lst)
		ft_token_lstclear(&data->token_lst);
	if (data->envp)
		free_two_dim(data->envp);
	close_all(data);
	exit (exit_code);
}
