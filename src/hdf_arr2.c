/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_arr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:54 by adeters           #+#    #+#             */
/*   Updated: 2025/03/21 15:21:44 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hdf_prompt_alloc(t_data *data, int nb)
{
	char	*nb_str;
	char	*prompt;
	int		size;

	if (data->hdf_amt == 1)
		return (ft_strdup(HERE_DOC_PROMPT));
	else
	{
		nb_str = ft_itoa(nb);
		if (!nb_str)
			return (NULL);
		size = ft_strlen(HERE_DOC_PROMPT) + ft_strlen(nb_str) + 4;
		prompt = ft_calloc(sizeof(char), size);
		if (!prompt)
			return (NULL);
		ft_strcpy(prompt, "[");
		ft_strcat(prompt, nb_str);
		ft_strcat(prompt, "] ");
		ft_strcat(prompt, HERE_DOC_PROMPT);
		return (free(nb_str), prompt);
	}
}

void	fill_hdf_help(t_data *data, int nb, char *delimiter, int fd)
{
	char	*line;
	char	*prompt;

	prompt = hdf_prompt_alloc(data, nb);
	if (!prompt)
		return (free(delimiter), rage_quit(data, ERR_MALLOC, true, NULL));
	line = readline(prompt);
	while (ft_strcmp(line, delimiter))
	{
		expand_env_var(data, &line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		free (prompt);
		prompt = hdf_prompt_alloc(data, nb);
		if (!prompt)
			return (free(delimiter), rage_quit(data, ERR_MALLOC, true, NULL));
		line = readline(prompt);
	}
	if (!line)
		p_hdf_int_warn(delimiter);
	return (free (line));
}

int	fill_hdf(t_data *data, char *hdf, char *delim, int nb)
{
	int		fd;

	fd = open(hdf, O_WRONLY);
	fill_hdf_help(data, nb, delim, fd);
	return (close(fd), 0);
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
