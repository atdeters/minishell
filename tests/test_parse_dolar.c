/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_dolar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:12:34 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/22 17:45:22 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

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
		printf("data input before parsing = %s\n", data.input);
		check_replace_input(&data);
		printf("data input after = %s\n", data.input);
	}
	write_hst_file(&data, HIST_FILE_PATH);
}