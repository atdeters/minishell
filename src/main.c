/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 18:42:29 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_shell(&data, env))
		return (pc_err(data.error));
	while (true)
	{
		if (init_command(&data))
			pnc_err(&data);
		if (data.init_com_fails == 0)
		{
			data.input = get_input(&data);
			if (add_full_history(&data))
				pnc_err(&data);
			if (!lexing(data.input, &data.token_lst, &data.error))
				pnc_err(&data);
			parser_main(&data.token_lst, &data);
			while (data.parsed_lst)
			{
				ft_printf("in main [0] = %s\n",
					data.parsed_lst->cmd_and_args[0]);
				execute(&data);
				data.parsed_lst = data.parsed_lst->next;
			}
			wait_all(&data);
			free(data.input);
		}
		if (data.init_com_fails >= MAX_INIT_COM_FAILS)
			return (pc_err(ERR_INIT_COM));
	}
	write_hst_file(&data, HIST_FILE_PATH);
}
