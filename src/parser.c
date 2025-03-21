/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:59 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/21 19:57:31 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd_array(t_token *current, t_token *tail, t_parsed **new,
		t_data *data)
{
	int	i;

	i = 0;
	while (current && current != tail->next)
	{
		if (!parse_in_out(current, new, data))
			return (free_p_node(*new), -1);
		if (check_for_count(current))
			i++;
		current = current->next;
	}
	(*new)->cmd_and_args = ft_calloc(i + 1, sizeof(char *));
	if (!(*new)->cmd_and_args)
		return (free_p_node(*new), data->error = ERR_MALLOC, -1);
	return (i);
}

/*
Used to be in this func:
		else if (check_for_putting_dollar(current))
		{
		(*new)->cmd_and_args[i] = return_from_env(*pars_data,
				current->value);
		if (!(*new)->cmd_and_args[i])
			return (0);
		i++;
		}
*/
static int	fill_cmd_array(t_token *current, t_token *tail, t_parsed **new)
{
	int	i;

	i = 0;
	while (current && current != tail->next)
	{
		if (check_for_putting_words(current))
		{
			(*new)->cmd_and_args[i] = ft_strdup(current->value);
			if (!(*new)->cmd_and_args[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	return (1);
}

static int	parse_command(t_pars_data *pars_data, t_data *data)
{
	t_parsed	*new;
	t_token		*current;
	int			array_size;

	new = create_p_node(NULL, NULL, NULL);
	if (!new)
		return (data->error = ERR_MALLOC, 0);
	if (!call_check_type(pars_data, new))
		return (data->error = ERR_MALLOC, 0);
	(pars_data->parsed_amount)++;
	current = pars_data->cur_head;
	array_size = init_cmd_array(current, pars_data->cur_tail, &new, data);
	if (array_size == -1)
		return (-1);
	if (!fill_cmd_array(current, pars_data->cur_tail, &new))
		return (free_p_node(new), data->error = ERR_MALLOC, -1);
	add_p_back(pars_data->parsed_lst, new);
	return (1);
}

static int	parser_loop(t_pars_data pars_data, t_data *data)
{
	t_token	*current;
	int		err;

	current = *(pars_data.token_lst);
	pars_data.cur_head = current;
	while (current)
	{
		if ((current->next && current->next->type == PIPE) || !current->next)
		{
			pars_data.cur_tail = current;
			err = parse_command(&pars_data, data);
			if (err == -1)
				return (free_p_lst(pars_data.parsed_lst), 0);
			else if (!err)
				return (0);
			pars_data.cur_head = current->next;
		}
		current = current->next;
	}
	return (1);
}

int	parser_main(t_data *data)
{
	t_pars_data	pars_data;
	t_parsed	*parse_lst;
	int			err;

	parse_lst = NULL;
	pars_data.parsed_lst = &parse_lst;
	init_pars_data(&pars_data, data, &data->token_lst);
	err = parser_loop(pars_data, data);
	if (data->error == ERR_MALLOC)
		rage_quit(data, data->error, true, NULL);
	if (!err)
		return (setnret(data, ERR_PARS));
	data->parsed_lst = *pars_data.parsed_lst;
	return (0);
}
