/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:14:52 by adeters           #+#    #+#             */
/*   Updated: 2025/03/25 18:43:12 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"
#include "signal.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_shell(&data, ac, av, env);
	pointer_to_data(&data);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, NULL);
	while (true)
	{
		init_command(&data);
		if (!(&data)->flag_single)
			get_input(&data);
		else
			(&data)->input = av[2];
		handle_pipeline(&data);
		if (data.flag_single)
			rage_quit(&data, data.exit_status, true, NULL);
	}
}

int	cmd_abort(t_data *data)
{
	data->exit_status = p_err(data, data->error);
	free_all_com(data);
	return (data->error);
}

int	handle_pipeline(t_data *data)
{
	if (!check_replace_input(data))
		return (cmd_abort(data));
	if (!lexing(data->input, &data->token_lst, data))
		p_err(data, data->error);
	expand_alias(data, &data->token_lst);
	create_hdf(data);
	if (fill_hdf_arr(data, &data->token_lst))
		return (cmd_abort(data));
	if (parser_main(data))
		p_err(data, data->error);
	pipe_maker(data);
	signal(SIGINT, SIG_IGN);
	while (data->parsed_lst && data->parsed_lst->next)
	{
		execute(data);
		data->pipe_ind++;
		data->parsed_lst = data->parsed_lst->next;
	}
	execute(data);
	close_all(data);
	wait_all(data);
	free_all_com(data);
	signal(SIGINT, signal_handler);
	return (0);
}
