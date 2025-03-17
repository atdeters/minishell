/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_arr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:54 by adeters           #+#    #+#             */
/*   Updated: 2025/03/17 21:50:08 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_hdf_help(t_data *data, int nb, char *delimiter, int fd)
{
	char	*line;

	hdf_prompt(data, nb);
	line = get_next_line(0);
	if (!line)
	{
		get_next_line(-1);
		free(delimiter);
		rage_quit(data, ERR_GNL, true, NULL);
	}
	while (ft_strcmp(line, delimiter))
	{
		expand_env_var(data, &line);
		write(fd, line, ft_strlen(line));
		free (line);
		hdf_prompt(data, nb);
		line = get_next_line(0);
		if (!line)
		{
			get_next_line(-1);
			free(delimiter);
			rage_quit(data, ERR_GNL, true, NULL);
		}
	}
	return (get_next_line(-1), free (line));
}

int	fill_hdf(t_data *data, char *hdf, char *delim, int nb)
{
	int		fd;
	char	*delimiter;

	fd = open(hdf, O_WRONLY);
	delimiter = delimiter_add_nl(delim);
	if (!delimiter)
		rage_quit(data, ERR_MALLOC, true, NULL);
	fill_hdf_help(data, nb, delimiter, fd);
	return (free(delimiter), close(fd), 0);
}

void	fill_hdf_arr_help(t_data *data, t_token **current, int i)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	(*current)->type = REDIR_IN;
	free ((*current)->value);
	(*current)->value = NULL;
	tmp = (*current)->next;
	new = create_token(WORD, ft_strdup(data->hdf_arr[i]));
	if (!new)
		rage_quit(data, ERR_MALLOC, true, NULL);
	(*current)->next = new;
	new->next = tmp;
	new->prev = *current;
	if (tmp)
		tmp->prev = new;
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
			fill_hdf(data, data->hdf_arr[i], current->value, nb);
			fill_hdf_arr_help(data, &current, i);
			i++;
			nb++;
		}
		current = current->next;
	}
	return (0);
}
