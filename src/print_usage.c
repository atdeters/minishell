/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreas <andreas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:49:03 by andreas           #+#    #+#             */
/*   Updated: 2025/03/10 00:27:12 by andreas          ###   ########.fr       */
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
		if (str[i] == '*')
		{
			if (!flag)
				printf(BOLD);
			else
				printf(RESET);
			flag = !flag;
		}
		else if (str[i] == '\\' && str[i + 1] == '*')
		{
			printf("*");
			i++;
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
	char	*full_path;
	int		fd;

	full_path = ft_strjoin(data->msh_path, path);
	if (!full_path)
		rage_quit(data, ERR_MALLOC, true, NULL);
	fd = open(full_path, O_RDONLY);
	free (full_path);
	if (fd < 0)
		rage_quit(data, ERR_OPEN, true, path);
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
}
