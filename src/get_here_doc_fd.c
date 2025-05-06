/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:46:04 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/**
 * Danger danger! Assumes the size of doc_file to be 15!!
 */
void	randon_filename_gen(t_data *data, char doc_file[15])
{
	ft_strcpy(doc_file, "/tmp/hdf_00000");
	while (!access(doc_file, F_OK))
	{
		if (add_random_end(doc_file, 5))
			rage_quit(data, ERR_CHILD, false, NULL);
	}
}
