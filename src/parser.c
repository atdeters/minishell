/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:59 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/23 20:51:11 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd_array(t_token *current, t_token *tail, t_parsed **new)
{
	int	i;

	i = 0;
	while (current && current != tail->next)
	{
		if (!parse_in_out(current, new))
			return (-1);
		if (check_for_count(current))
			i++;
		current = current->next;
	}
	(*new)->cmd_and_args = malloc(sizeof(char *) * (i + 1));
	if (!(*new)->cmd_and_args)
		return (-1);
	(*new)->cmd_and_args[i] = NULL;
	return (i);
}

static int	fill_cmd_array(t_token *current, t_token *tail, t_parsed **new,
		t_pars_data *pars_data)
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
		else if (check_for_putting_dollar(current))
		{
			(*new)->cmd_and_args[i] = return_from_env(*pars_data,
					current->value);
			if (!(*new)->cmd_and_args[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	return (1);
}

static int	parse_command(t_pars_data *pars_data)
{
	t_parsed	*new;
	t_token		*current;
	int			array_size;

	new = create_p_node(NULL, NULL, NULL);
	if (!new)
		return (0);
	call_check_type(pars_data, new);
	(*pars_data).parsed_amount++;
	current = (*pars_data).cur_head;
	array_size = init_cmd_array(current, (*pars_data).cur_tail, &new);
	if (array_size == -1)
		return (0);
	if (!fill_cmd_array(current, (*pars_data).cur_tail, &new, pars_data))
		return (0);
	add_p_back(pars_data->parsed_lst, new);
	return (1);
}

static int	parser_loop(t_pars_data pars_data)
{
	t_token	*current;

	current = *(pars_data.token_lst);
	pars_data.cur_head = current;
	while (current)
	{
		if ((current->next && current->next->type == PIPE) || !current->next)
		{
			pars_data.cur_tail = current;
			if (!parse_command(&pars_data))
				return (0);
			pars_data.cur_head = current->next;
		}
		current = current->next;
	}
	return (1);
}

// int	parser_main(t_token **tokens, t_data *data)
// {
// 	t_pars_data	pars_data;
// 	t_parsed	*parse_lst;

// 	parse_lst = NULL;
// 	pars_data.parsed_lst = &parse_lst;
// 	init_pars_data(&pars_data, data, tokens);
// 	if (!parser_loop(pars_data))
// 		return (data->error = ERR_PARS, 0);
// 	(*data).parsed_lst = *pars_data.parsed_lst;
// 	ft_token_lstclear(tokens);
// 	return (1);
// }

int	parser_main(t_data *data)
{
	t_pars_data	pars_data;
	t_parsed	*parse_lst;

	parse_lst = NULL;
	pars_data.parsed_lst = &parse_lst;
	init_pars_data(&pars_data, data, &data->token_lst);
	if (!parser_loop(pars_data))
		return (setnret(data, ERR_PARS));
	(*data).parsed_lst = *pars_data.parsed_lst;
	ft_token_lstclear(&data->token_lst);
	return (0);
}