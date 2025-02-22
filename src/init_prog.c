/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:03:22 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 18:51:59 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_help(void)
{
	char	*line;
	int		fd;

	fd = open(HELP_FILE_PATH, O_RDONLY);
	if (fd < 0)
		exit (ERR_OPEN);
	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		exit (ERR_MALLOC);
	}
	while (line)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	exit (0);
}

int	init_shell(t_data *data, int ac, char **av, char **env)
{
	if (ac != 1 && ac != 3 && ac != 2)
		return (pc_err(ERR_USAGE));
	*data = (t_data){0};
	if (check_flags(data, ac, av))
		return (data->error);
	parse_env(data, env);
	parser_env_into_arr(data);
	load_old_history(HIST_FILE_PATH);
	return (data->error);
}
