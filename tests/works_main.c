/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 17:43:37 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data; 

	data = (t_data){0};
	data.single_flag = true;
	if (ac == 3 && !ft_strncmp(av[1], "--single", ft_strlen(av[1])))
		data.single = true;
	else if (ac == 3 && !ft_strncmp(av[1], "-s", ft_strlen(av[1])))
		data.single = true;
	else
		data.single = false;
	if (ac != 1 && (ac != 3))
		return (pc_err(ERR_USAGE));
	if (init_shell(&data, env))
		return (pc_err(data.error));
	while (true && data.single_flag)
	{
		if (init_command(&data))
			pnc_err(&data);
		if (!data.single)
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
		if (!data.single)
			free(data.input);
		if (data.single)
			data.single_flag = false;
	}
	write_hst_file(&data, HIST_FILE_PATH);
}
