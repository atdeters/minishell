/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 18:14:54 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data; 

	if (init_shell(&data, ac, av, env))
		return (pc_err(data.error));
	while (true && data.flag_single_switch)
	{
		if (init_command(&data))
			pnc_err(&data);
		if (!data.flag_single)
			data.input = get_input(&data);
		else
			data.input = av[2];
		if (add_full_history(&data))
			pnc_err(&data);
		if (!check_replace_input(&data))
			pnc_err(&data);
		if(!lexing(data.input, &data.token_lst, &data.error))
			pnc_err(&data);
		if(!parser_main(&data.token_lst, &data))
			pnc_err(&data);
		pipe_maker(&data);
		while (data.parsed_lst)
		{
			execute(&data);
			data.parsed_lst = data.parsed_lst->next;
		}
		close_all(&data);
		wait_all(&data);
		if (!data.flag_single)
			free(data.input);
		if (data.flag_single)
			data.flag_single_switch = false;
	}
	write_hst_file(&data, HIST_FILE_PATH);
}
