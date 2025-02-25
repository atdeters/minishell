/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/25 15:21:20 by adeters          ###   ########.fr       */
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

void	chp(void)
{
	static int	pos;

	printf("Checkpoint %d successful!\n", pos);
	pos++;
}

bool	needs_expand(t_data *data, char *current, t_token *tmp)
{
	if (!tmp->prev && ft_strcmp(current, tmp->value))
		return (true);
	else if (tmp->prev && tmp->prev->type != WORD && ft_strcmp(current,
			tmp->value))
		return (true);
	return (false);
}

int	expand_alias(t_data *data, t_token **lst)
{
	t_token	*tmp;
	t_token	*last;
	t_token	*old;
	t_token	*expanded;
	char	*current;

	tmp = *lst;
	expanded = NULL;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			current = get_value_from_lst(data->alias_lst, tmp->value);
			if (!current)
				rage_quit(data, ERR_MALLOC, true);
			if (needs_expand(data, current, tmp))
			{
				current = rid_of_nl(current);
				if (!lexing(current, &expanded, &data->error))
				{
					free(current);
					rage_quit(data, ERR_LEXING, true);
				}
				last = ft_token_lstlast(expanded);
				last->next = tmp->next;
				old = tmp;
				if (tmp->prev)
					tmp->prev->next = expanded;
				else
					data->token_lst = expanded;
				ft_token_lstdelone(old);
				tmp = last;
			}
			free(current);
		}
		tmp = tmp->next;
	}
	return (0);
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
	// Maybe do here_doc here; than change the in_mode to file
	// and add the filename to it
	if (parser_main(data))
		pnc_err(data);
	if (pipe_maker(data))
		pnc_err(data);
	while (data->parsed_lst)
	{
		execute(data);
		data->parsed_lst = data->parsed_lst->next;
	}
	close_all(data);
	wait_all(data);
	if (data->exit_status == ERR_CHILD)
		rage_quit(data, ERR_CHILD, true);
	free_all_com(data);
	return (0);
}
