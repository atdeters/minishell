/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:49:03 by andreas           #+#    #+#             */
/*   Updated: 2025/03/07 17:49:04 by andreas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BOLD  "\033[1m"
#define RESET "\033[0m"

void	print_with_bold(char *str)
{
	bool	flag;
	int		i;

	i = 0;
	flag = false;
	while (str[i])
	{
		if (str[i] == '*' && !flag)
		{
			printf(BOLD);
			flag = true;
		}
		else if (str[i] == '*' && flag)
		{
			printf(RESET);
			flag = false;
		}
		else
			printf("%c", str[i]);
		i++;
	}
	printf(RESET);
}

void	print_usage(t_data *data, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit (ERR_OPEN);
	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		rage_quit(data, ERR_GNL, true, NULL);
	}
	while (line)
	{
		print_with_bold(line);
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	exit (0);
}
