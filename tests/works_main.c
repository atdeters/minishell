/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 19:12:59 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	// t_token *t_lst;

	if (init_shell(&data, env))
		return (pc_err(data.error));
	data.env_lst = NULL;
	while (true)
	{
		// t_lst = NULL;
		if (init_command(&data))
			pnc_err(&data);
		// data.parsed_lst = NULL;
		// data.token_lst = NULL;
		if (data.init_com_fails == 0)
		{
			data.input = get_input(&data);
			if (add_full_history(&data))
				pnc_err(&data);
			lexing(data.input, &data.token_lst);
			parse_env(&data, env);
			parser_main(&data.token_lst, &data);
			pipe_maker(&data);
			while (data.parsed_lst)
			{
				execute(&data);
				data.parsed_lst = data.parsed_lst->next;
			}
			close_all(&data);
			wait_all(&data);
			free(data.input);
		}
		if (data.init_com_fails >= MAX_INIT_COM_FAILS)
			return (pc_err(ERR_INIT_COM));
	}
	write_hst_file(&data, HIST_FILE_PATH);
}
