/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 18:08:24 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac == 3 && !ft_strncmp(av[1], "-c", ft_strlen(av[1])))
		data.single = 1;
	if (ac != 1 || (ac != 3 && ft_strncmp(av[1], "-c", ft_strlen(av[1]))))
		return (pc_err(ERR_USAGE));
	if (init_shell(&data, env))
		return (pc_err(data.error));
	while (true && data.single)
	{
		if (init_command(&data))
			pnc_err(&data);
		if (data.init_com_fails == 0)
		{
			if (!data.single)
				data.input = get_input(&data);
			else
				data.input = av[2];
			if (add_full_history(&data))
				pnc_err(&data);
			lexing(data.input, &data.token_lst);
			parser_main(&data.token_lst, &data);
			pipe_maker(&data);
			while (data.parsed_lst)
			{
				if (data.parsed_lst->out_mode == OUT_MODE_PIPE)
					data.ind_out_pipe++;
				if (data.parsed_lst->in_mode == IN_MODE_PIPE)
					data.ind_in_pipe++;
				execute(&data);
				data.parsed_lst = data.parsed_lst->next;
			}
			close_all(&data);
			wait_all(&data);
			if (!data.single)
				free(data.input);
		}
		if (data.init_com_fails >= MAX_INIT_COM_FAILS)
			return (pc_err(ERR_INIT_COM));
		data.single = 0;
	}
	write_hst_file(&data, HIST_FILE_PATH);
}
