/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:36:15 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	load_old_history(char *hist_file_path)
{
	int		fd;
	char	*entry;

	if (!hist_file_path)
		return (1);
	fd = open(hist_file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	entry = get_next_line(fd);
	if (!entry)
		return (close (fd), 1);
	entry = rid_of_nl(entry);
	while (entry)
	{
		add_history(rid_of_nl(entry));
		free (entry);
		entry = get_next_line(fd);
	}
	return (close(fd), 0);
}

int	add_full_history(t_data *data)
{
	char	*lst_entry;
	t_list	*node;

	if (ft_strcmp(data->input, ""))
	{
		add_history(data->input);
		lst_entry = ft_strdup(data->input);
		if (!lst_entry)
			return (setnret(data, ERR_HIST));
		node = ft_lstnew(lst_entry);
		if (!node)
			return (free(lst_entry), setnret(data, ERR_HIST));
		ft_lstadd_back(&data->hstlst, node);
	}
	return (0);
}

int	write_hst_file(t_data *data, char *hist_file_path)
{
	int		fd;
	t_list	*tmp;

	tmp = data->hstlst;
	if (!hist_file_path)
		return (setnret(data, ERR_HIST_WFILE));
	fd = open(hist_file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return (setnret(data, ERR_HIST_WFILE));
	while (tmp && tmp->next)
	{
		write(fd, tmp->content, ft_strlen(tmp->content));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	if (tmp)
	{
		write(fd, tmp->content, ft_strlen(tmp->content));
		write(fd, "\n", 1);
	}
	return (close(fd), 0);
}

int	free_hst_list(t_data *data)
{
	t_list	*pre;

	while (data->hstlst && data->hstlst->next)
	{
		free(data->hstlst->content);
		pre = data->hstlst;
		data->hstlst = data->hstlst->next;
		free (pre);
	}
	if (data->hstlst)
	{
		free(data->hstlst->content);
		free (data->hstlst);
	}
	data->hstlst = NULL;
	return (0);
}
