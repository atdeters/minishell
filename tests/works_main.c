/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 17:38:18 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	handle_prompt(t_data *data, char **av);

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_shell(&data, ac, av, env))
		return (pc_err(data.error));
	while (true)
	{
		if (handle_prompt(&data, av))
			rage_quit(&data, data.error, true);
		if (data.flag_single)
			rage_quit(&data, 0, true);
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
	if (lexing(data))
		pnc_err(data);
	// Maybe do here_doc here; than change the in_mode to file
	// and add the filename to it
	if (parser_main(data))
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
	if (data->exit_status == ERR_CHILD)
		rage_quit(data, ERR_CHILD, true);
	free_all_com(data);
	return (0);
}
