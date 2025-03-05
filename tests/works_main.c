/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 16:41:38 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int		handle_pipeline(t_data *data, char **av);

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_shell(&data, ac, av, env);
	while (true)
	{
		handle_pipeline(&data, av);
		if (data.flag_single)
			rage_quit(&data, data.exit_status, true, NULL);
	}
}

int	handle_pipeline(t_data *data, char **av)
{
	init_command(data);
	if (!data->flag_single)
		get_input(data);
	else
		data->input = av[2];
	if (check_replace_input(data))
		p_err(data->error);
	if (!lexing(data->input, &data->token_lst, &data->error))
		p_err(data->error);
	if (!data->token_lst)
		return (free_all_com(data), 0);
	expand_alias(data, &data->token_lst);
	create_hdf(data);
	fill_hdf_arr(data, &data->token_lst);
	if (parser_main(data))
		p_err(data->error);
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
	free_all_com(data);
	return (0);
}
