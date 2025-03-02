/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/03/01 16:57:51 by adeters          ###   ########.fr       */
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
	if (expand_alias(data, &data->token_lst))
		pnc_err(data);
	if (create_hdf(data))
		pnc_err(data);
	if (fill_hdf_arr(data, &data->token_lst))
		pnc_err(data);
	if (parser_main(data))
		pnc_err(data);
	if (pipe_maker(data))
		pnc_err(data);
	while (data->parsed_lst->next)
	{
		execute(data);
		data->pipe_ind++;
		data->parsed_lst = data->parsed_lst->next;
	}
	execute(data);
	close_all(data);
	wait_all(data);
	if (data->exit_status == ERR_CHILD)
		rage_quit(data, ERR_CHILD, true, NULL);
	free_all_com(data);
	return (0);
}
