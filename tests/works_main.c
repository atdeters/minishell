/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/20 19:50:58 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		pid;

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
		pid = fork();
		if (pid == 0)
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
				if(!lexing(data.input, &data.token_lst, &data.error))
					pnc_err(&data);
				if(!parser_main(&data.token_lst, &data))
					pnc_err(&data);
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
			// Doesn't work anymore at this point
			if (data.init_com_fails >= MAX_INIT_COM_FAILS)
				return (pc_err(ERR_INIT_COM));
			if (data.single)
				data.single_flag = false;
		}
		if (pid == -1)
			return (pc_err(ERR_FORK));
		waitpid(pid, &data.exit_status, 0);
		if (WIFEXITED(data.exit_status))
			WEXITSTATUS(data.exit_status);
	}
	write_hst_file(&data, HIST_FILE_PATH);
}
