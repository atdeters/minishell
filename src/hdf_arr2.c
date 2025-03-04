/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_arr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:54 by adeters           #+#    #+#             */
/*   Updated: 2025/02/28 18:28:50 by adeters          ###   ########.fr       */
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
		rage_quit(data, ERR_MALLOC, true, NULL);
	hdf_prompt(data, nb);
	line = get_next_line(0);
	if (!line)
	{
		free(delimiter);
		rage_quit(data, ERR_GNL, true, NULL);
	}
	while (ft_strcmp(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		hdf_prompt(data, nb);
		free (line);
		line = get_next_line(0);
		if (!line)
		{
			free(delimiter);
			rage_quit(data, ERR_GNL, true, NULL);
		}
	}
	return (free(delimiter), free(line), close(fd), 0);
}

int	fill_hdf_arr(t_data *data, t_token **lst)
{
	t_token	*current;
	t_token *new;
	t_token	*tmp;
	int		i;
	int		nb;

	current = *lst;
	i = 0;
	nb = 0;
	while (current)
	{
		new = NULL;
		if (current->type == DELIMITER)
		{
			fill_hdf(data, data->hdf_arr[i], current->value, nb);
			current->type = REDIR_IN;
			free (current->value);
			current->value = NULL;
			tmp = current->next;
			new = create_token(WORD, ft_strdup(data->hdf_arr[i])); // strdup save here?
			if (!new)
				rage_quit(data, ERR_MALLOC, true, NULL);
			current->next = new;
			new->next = tmp;
			new->prev = current;
			if (tmp)
				tmp->prev = new;
			i++;
			nb++;
		}
		current = current->next;
	}
	return (0);
}
