/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_arr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:54 by adeters           #+#    #+#             */
/*   Updated: 2025/02/27 19:26:02 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_hdf(t_data *data, char *hdf, char *delim, int nb)
{
	int		fd;
	char	*delimiter;
	char	*line;

	fd = open(hdf, O_WRONLY);
	delimiter = delimiter_add_nl(delim);
	if (!delimiter)
		return (setnret(data, ERR_MALLOC));
	hdf_prompt(data, nb);
	line = get_next_line(0);
	if (!line)
		return (free(delimiter), setnret(data, ERR_GNL));
	while (ft_strcmp(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		hdf_prompt(data, nb);
		free (line);
		line = get_next_line(0);
		if (!line)
			return (free(delimiter), setnret(data, ERR_GNL));
	}
	return (free(delimiter), free(line), close(fd), 0);
}

int	fill_hdf_arr(t_data *data, t_token **lst)
{
	t_token	*current;
	int		i;
	int		nb;

	current = *lst;
	i = 0;
	nb = 0;
	while (current)
	{
		if (current->type == DELIMITER)
		{
			if (fill_hdf(data, data->hdf_arr[i], current->value, nb))
				return (data->error);
			current->type = REDIR_IN;
			free (current->value);
			current->value = ft_strdup(data->hdf_arr[i]);
			if (!current->value)
				return (setnret(data, ERR_MALLOC));
			i++;
		}
		current = current->next;
		nb++;
	}
	return (0);
}
