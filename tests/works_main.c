/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 19:39:25 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int handle_prompt(t_data *data, char **av);

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_shell(&data, ac, av, env))
		return (pc_err(data.error));
	while (data.on)
	{
		if (handle_prompt(&data, av))
			rage_quit(&data, data.error);
		if (data.flag_single)
			data.on = false;
	}
	rage_quit(&data, 0);
}

int	handle_prompt(t_data *data, char **av)
{
	init_command(data);
	if (!data->flag_single)
		data->input = get_input(data);
	else
		data->input = av[2];
	if (add_full_history(data))
		pnc_err(data);
	if (!check_replace_input(data))
		pnc_err(data);
	if (!lexing(data->input, &data->token_lst, &data->error))
		pnc_err(data);
	if (!parser_main(&data->token_lst, data))
		pnc_err(data);
	if (pipe_maker(data))
		pnc_err(data);
	while (data->parsed_lst)
	{
		execute(data);
		data->parsed_lst = data->parsed_lst->next;
	}
	close_all(data);
	wait_all(data);
	if (!data->flag_single)
		free(data->input);
	return (0);
}
