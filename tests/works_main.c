/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/27 18:22:15 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int		handle_prompt(t_data *data, char **av);

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_shell(&data, ac, av, env))
		return (pc_err(data.error));
	while (true)
	{
		if (handle_prompt(&data, av))
			rage_quit(&data, data.error, true);
		if (data.flag_single)
			rage_quit(&data, 0, true);
	}
}






// Count amount of pipes
int	hdf_counter(t_token *lst)
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
	return (counter);
}

char	*hdf_name_gen(t_data *data)
{
	char doc_file[15];

	ft_strcpy(doc_file, "/tmp/hdf_XXXXX");
	while (!access(doc_file, F_OK))
	{
		if (add_random_end(doc_file, 5))
			rage_quit(data, ERR_CHILD, false);
	}
	return (ft_strdup(doc_file));
}

int	create_hdf(t_data *data)
{
	int		amt;
	int		i;
	int		fd;

	amt = hdf_counter(data->token_lst);
	data->hdf_arr = malloc(sizeof(char *) * (amt + 1));
	if (!data->hdf_arr)
		return (setnret(data, ERR_MALLOC));
	data->hdf_arr[amt] = NULL;
	i = 0;
	while (i < amt)
	{
		data->hdf_arr[i] = hdf_name_gen(data);
		if (!data->hdf_arr[i])
			rage_quit(data, ERR_MALLOC, true);
		fd = open(data->hdf_arr[i], O_CREAT, 0600);
		if (fd < 0)
			return (setnret(data, ERR_OPEN));
		close (fd);
		i++;
	}
	return (0);
}

int	fill_hdf_arr(t_data *data)
{
	t_token	*current;
	char	*delimiter;
	char	*line;
	int		i;
	int		fd;

	current = data->token_lst;
	i = 0;
	while (current)
	{
		if (current->type == DELIMITER)
		{
			fd = open(data->hdf_arr[i], O_WRONLY);
			printf("%s%%\n", current->value);
			delimiter = delimiter_add_nl(current->value);
			if (!delimiter)
				return (setnret(data, ERR_MALLOC));
			ft_printf("%s", HERE_DOC_PROMPT);
			line = get_next_line(0);
			if (!line)
				return (free(delimiter), setnret(data, ERR_GNL));
			while (ft_strcmp(line, delimiter))
			{
				write(fd, line, ft_strlen(line));
				ft_printf("%s", HERE_DOC_PROMPT);
				free (line);
				line = get_next_line(0);
				if (!line)
					return (free(delimiter), setnret(data, ERR_GNL));
			}
			free(delimiter);
			free(line);
			close (fd);
			i++;
		}
		current = current->next;
	}
}










int	handle_prompt(t_data *data, char **av)
{
	init_command(data);
	if (!data->flag_single)
		get_input(data);
	else
		data->input = av[2];
	if (check_replace_input(data))
		pnc_err(data);
	if (!lexing(data->input, &data->token_lst, &data->error))
		pnc_err(data);
	if (expand_alias(data, &data->token_lst))
		pnc_err(data);

	
	if (create_hdf(data))
		pnc_err(data);
	fill_hdf_arr(data);

	
	// Maybe do here_doc here; than change the in_mode to file
	// and add the filename to it
	if (parser_main(data))
		pnc_err(data);
	if (pipe_maker(data))
		pnc_err(data);
	while (data->parsed_lst->next)
	{
		execute(data);
		data->parsed_lst = data->parsed_lst->next;
	}
	execute(data);
	close_all(data);
	wait_all(data);
	if (data->exit_status == ERR_CHILD)
		rage_quit(data, ERR_CHILD, true);
	free_all_com(data);
	return (0);
}
