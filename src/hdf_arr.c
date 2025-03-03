/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdf_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:29:01 by adeters           #+#    #+#             */
/*   Updated: 2025/02/27 19:47:28 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hdf_counter(t_data *data, t_token *lst)
{
	t_token	*current;
	int		counter;

	counter = 0;
	current = lst;
	while (current)
	{
		if (current->type == DELIMITER)
			counter++;
		current = current->next;
	}
	data->hdf_amt = counter;
	return (counter);
}

char	*hdf_name_gen(t_data *data)
{
	char	doc_file[15];

	ft_strcpy(doc_file, "/tmp/hdf_XXXXX");
	while (!access(doc_file, F_OK))
	{
		if (add_random_end(doc_file, 5))
			rage_quit(data, ERR_CHILD, false, NULL);
	}
	return (ft_strdup(doc_file));
}

int	create_hdf(t_data *data)
{
	int		amt;
	int		i;
	int		fd;

	amt = hdf_counter(data, data->token_lst);
	data->hdf_arr = malloc(sizeof(char *) * (amt + 1));
	if (!data->hdf_arr)
		rage_quit(data, ERR_MALLOC, true, NULL);
	data->hdf_arr[amt] = NULL;
	i = 0;
	while (i < amt)
	{
		data->hdf_arr[i] = hdf_name_gen(data);
		if (!data->hdf_arr[i])
			rage_quit(data, ERR_MALLOC, true, NULL);
		fd = open(data->hdf_arr[i], O_CREAT, 0777);
		if (fd < 0)
			rage_quit(data, ERR_OPEN, true, data->hdf_arr[i]);
		close (fd);
		i++;
	}
	return (0);
}

void	hdf_prompt(t_data *data, int nb)
{
	if (data->hdf_amt == 1)
		ft_printf("%s", HERE_DOC_PROMPT);
	else
		ft_printf("[%d] %s", nb, HERE_DOC_PROMPT);
}
