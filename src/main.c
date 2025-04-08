/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:14:52 by adeters           #+#    #+#             */
/*   Updated: 2025/04/08 13:48:10 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"
#include "signal.h"

int	cmd_abort(t_data *data, bool mute)
{
	if (err_is_critical(data->error))
	{
		data->exit_status = data->error;
		rage_quit(data, data->error, true, NULL);
	}
	if (mute)
		data->exit_status = data->error;
	else
		data->exit_status = p_err(data->error);
	free_all_com(data);
	return (data->error);
}

int	handle_pipeline(t_data *data)
{
	if (!check_replace_input(data))
		return (cmd_abort(data, false));
	if (!lexing(data->input, &data->token_lst, data))
		return (cmd_abort(data, false));
	t_token *tmp;
	tmp = data->token_lst;
	while (tmp)
	{
		printf("token->value = |%s|, token->type = %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	expand_alias(data, &data->token_lst);
	create_hdf(data);
	if (fill_hdf_arr(data, &data->token_lst))
		return (cmd_abort(data, true));
	if (parser_main(data))
		return (cmd_abort(data, false));
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
	signal(SIGINT, sig_handle_basic);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_shell(&data, ac, av, env);
	signal(SIGINT, sig_handle_basic);
	signal(SIGQUIT, SIG_IGN);
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
