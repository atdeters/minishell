/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/03/03 16:23:45 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int		handle_prompt(t_data *data, char **av);

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_shell(&data, ac, av, env))
		return (pc_err(data.error));
	while (true)
	{
		if (handle_prompt(&data, av))
			rage_quit(&data, data.error, true, NULL);
		if (data.flag_single)
			rage_quit(&data, 0, true, NULL);
	}
}

int	handle_prompt(t_data *data, char **av)
{
	init_command(data);
	if (!data->flag_single)
		get_input(data);
	else
		data->input = av[2];
	if (check_replace_input(data))
		pnc_err(data);
	if (!lexing(data->input, &data->token_lst, &data->error))
		pnc_err(data);
	if (!data->token_lst)
		return (free_all_com(data), 0);
	expand_alias(data, &data->token_lst);
	create_hdf(data);
	fill_hdf_arr(data, &data->token_lst);
	if (parser_main(data))
		pnc_err(data);
	pipe_maker(data);
	while (data->parsed_lst->next)
	{
		execute(data);
		data->pipe_ind++;
		data->parsed_lst = data->parsed_lst->next;
	}
	execute(data);
	close_all(data);
	wait_all(data);
	if (data->exit_status / 100 == 2)
		rage_quit(data, data->exit_status, true, NULL);
	free_all_com(data);
	return (0);
}
