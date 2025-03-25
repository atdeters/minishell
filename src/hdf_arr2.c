/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_arr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:54 by adeters           #+#    #+#             */
/*   Updated: 2025/03/25 20:42:10 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_and_free(int fd, char *line, char *prompt)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	free(prompt);
}

int	fill_hdf_help(t_data *data, int nb, char *delimiter, int fd)
{
	char	*line;
	char	*prompt;

	prompt = hdf_prompt_alloc(data, nb);
	if (!prompt)
		return (close(fd), free(delimiter), rage_quit(data, ERR_MALLOC, true,
				NULL), 0);
	line = readline(prompt);
	while (ft_strcmp(line, delimiter) && !g_signal)
	{
		if (!expand_env_var(data, &line))
			return (free(line), free(prompt), close(fd), free(delimiter),
				rage_quit(data, ERR_MALLOC, true, NULL), 0);
		write_and_free(fd, line, prompt);
		prompt = hdf_prompt_alloc(data, nb);
		if (!prompt)
			return (close(fd), free(delimiter), rage_quit(data, ERR_MALLOC,
					true, NULL), 0);
		line = readline(prompt);
	}
	if (g_signal)
		return (free(prompt), free(line), setnret(data, ERR_PARS), 1);
	if (!line)
		p_hdf_int_warn(delimiter);
	return (free(prompt), free(line), 0);
}

int	fill_hdf(t_data *data, char *hdf, char *delim, int nb)
{
	int	fd;
	int	ret;

	fd = open(hdf, O_WRONLY);
	if (fd < 0)
		rage_quit(data, ERR_OPEN, true, NULL);
	signal(SIGINT, sig_handle_here_doc);
	ret = fill_hdf_help(data, nb, delim, fd);
	signal(SIGINT, sig_handle_basic);
	return (close(fd), ret);
}

void	fill_hdf_arr_help(t_data *data, t_token **current, int i)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	(*current)->type = REDIR_IN;
	free((*current)->value);
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
			if (fill_hdf(data, data->hdf_arr[i], current->value, nb))
				return (data->error);
			fill_hdf_arr_help(data, &current, i);
			i++;
			nb++;
		}
		current = current->next;
	}
	return (0);
}
