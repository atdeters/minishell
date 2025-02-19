/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 18:44:23 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	// t_token *t_lst;

	if (init_shell(&data, env))
		return (pc_err(data.error));
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
			// printf("data.token_lst->value = %s\n", data.token_lst->value);
			parser_main(&data.token_lst, &data);
			ft_printf("data.parsed_lst->cmd_and[0] = %s\n",
				data.parsed_lst->cmd_and_args[0]);
			while (data.parsed_lst)
			{
				ft_printf("in main [0] = %s\n",
					data.parsed_lst->cmd_and_args[1]);
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
