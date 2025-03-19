/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:14:52 by adeters           #+#    #+#             */
/*   Updated: 2025/03/19 17:31:07 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

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

int	handle_pipeline(t_data *data)
{
	if (check_replace_input(data))
		p_err(data, data->error);
	if (!lexing(data->input, &data->token_lst, &data->error))
		p_err(data, data->error);
	expand_alias(data, &data->token_lst);
	// Make create_hdf return bool to check for SIGINT
	create_hdf(data);
	fill_hdf_arr(data, &data->token_lst);
	if (parser_main(data))
		p_err(data, data->error);
	pipe_maker(data);
	data->block_sig = true;
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
	data->block_sig = false;
	return (0);
}
