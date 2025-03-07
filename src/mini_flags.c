/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:51:33 by adeters           #+#    #+#             */
/*   Updated: 2025/03/07 18:43:05 by andreas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag_single(char *flag)
{
	int	i;

	if (!ft_strcmp(flag, "--single"))
		return (true);
	if (!ft_strcmp(flag, "-s"))
		return (true);
	i = 1;
	if (flag[0] != '-')
		return (false);
	while (flag[i])
	{
		if (flag[i] != 's')
			return (false);
		i++;
	}
	return (true);
}

bool	is_flag_help(char *flag)
{
	if (!ft_strcmp(flag, "--help"))
		return (true);
	return (false);
}

int	check_flags(t_data *data, int ac, char **av)
{
	if (ac == 3 && is_flag_single(av[1]))
		data->flag_single = true;
	else if (ac == 3)
		rage_quit(data, ERR_USAGE, true, NULL);
	else
		data->flag_single = false;
	if (ac == 2 && is_flag_help(av[1]))
	{
		// print_help();
		print_usage(data, HELP_FILE_PATH);
		return (exit(0), 0);
	}
	else if (ac == 2)
		rage_quit(data, ERR_USAGE, true, NULL);
	return (0);
}

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
