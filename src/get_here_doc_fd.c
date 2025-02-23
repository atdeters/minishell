/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:46:04 by adeters           #+#    #+#             */
/*   Updated: 2025/02/23 17:12:12 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delimiter_add_nl(char *delimiter_old)
{
	char	*delimiter;
	int		size;

	if (!delimiter_old)
		return (NULL);
	size = ft_strlen(delimiter_old) + 2;
	delimiter = ft_calloc(sizeof(char), size);
	if (!delimiter)
		return (NULL);
	ft_strlcpy(delimiter, delimiter_old, size - 1);
	delimiter[size - 2] = '\n';
	return (delimiter);
}

int	add_random_end(char *doc_file, int amount)
{
	int		fd_rnd;
	int		i;
	int		j;
	char	buff_ch;

	fd_rnd = open("/dev/urandom", O_RDONLY);
	if (fd_rnd < 0)
		return (1);
	i = ft_strlen(doc_file) - 1;
	j = 0;
	while (j < amount)
	{
		read(fd_rnd, &buff_ch, 1);
		if (ft_isalnum(buff_ch))
		{
			doc_file[i] = buff_ch;
			i--;
			j++;
		}
	}
	doc_file[ft_strlen(doc_file)] = '\0';
	close (fd_rnd);
	return (0);
}

int	get_here_doc_fd(t_data *data, char *delimiter)
{
	char	doc_file[15];
	int		fd;
	char	*line;

	ft_strcpy(doc_file, "/tmp/hdf_00000");
	while (!access(doc_file, F_OK))
	{
		if (add_random_end(doc_file, 5))
			rage_quit(data, ERR_CHILD, false);
	}
	fd = open(doc_file, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (fd < 0)
		return (-1);
	delimiter = delimiter_add_nl(delimiter);
	if (!delimiter)
		return (0);
	ft_printf("here_doc> ");
	line = get_next_line(0);
	if (!line)
			return (free(delimiter), -1);
	while (ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		// Add variable expansion here
		write(fd, line, ft_strlen(line));
		ft_printf("here_doc> ");
		free (line);
		line = get_next_line(0);
		if (!line)
			return (free(delimiter), -1);
	}
	free(delimiter);
	free(line);
	close (fd);
	fd = open(doc_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}
