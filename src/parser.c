/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:59 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/17 17:16:17 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
I also should take env_lst, becasue after parsind I will not know where should I put vatiables

Possbile shit with redirection:
cat < Makefile >> infile
< Makefile >>infile cat
>infile cat <Makefile
cat <some
< some cat
So cmd can be everywhere BUT after redirection sign it alway should be filename 
FUNNY/IMPORTANT: infile > cat1 ||->>> This will create file with name cat1

Example to work with:
wc < Makefile -w | >> infile cat | echo $user | cat ""

After lexing it will be:
type: 0, value: wc 
type: 5, value: (null)
type: 0, value: Makefile 
type: 0, value: -w 
type: 4, value: (null)
type: 8, value: (null)
type: 0, value: infile 
type: 0, value: cat 
type: 4, value: (null)
type: 0, value: echo 
type: 3, value: user 
type: 4, value: (null)
type: 0, value: cat 
type: 2, value: 

What i want to get: 
cmd_and_args = ["wc", "-w", NULL]
in = Makefile
in_mode = IN_MODE_FILE
out = PIPE
out_mode = OUT_MODE_PIPE
prew->NULL
next -> next

cmd_and_args = ["cat",  NULL]
in = PIPE
in_mode = IN_MODE_PIPE
out = infile
out_mode = OUT_MODE_FILE_APP
prew->prew
next -> next

cmd_and_args = ["echo", "{user=value}" NULL]
in = PIPE
in_mode = IN_MODE_PIPE
out = PIPE
out_mode = OUT_MODE_PIPE
prew->prew
next -> next

cmd_and_args = ["cat", "", NULL]
in = PIPE
in_mode = IN_MODE_PIPE
out = OUT_STD
out_mode = OUT_MODE_STD
prew->prew
next -> NULL
*/

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

static int	fill_cmd_array(t_token *current, t_token *tail, t_parsed **new, t_pars_data *pars_data)
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
			(*new)->cmd_and_args[i] = return_from_env(*pars_data, current->value);
			if ((*new)->cmd_and_args[i] == NULL)
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
	call_check_type(pars_data, new);
	(*pars_data).parsed_amount++;
	current = (*pars_data).cur_head;

	array_size = init_cmd_array(current, (*pars_data).cur_tail, &new);
	if (array_size == -1)
		return (0);

	if (!fill_cmd_array(current, (*pars_data).cur_tail, &new, pars_data))
		return (0);

	add_p_back((*pars_data).parsed_lst, new);
	return (1);
}

static int	parser_loop(t_pars_data pars_data)
{
	t_token *current;

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

int	parser_main(t_token **tokens, t_data *data)
{
	t_pars_data pars_data;

	init_pars_data(&pars_data, data, tokens);
	if (pars_data.cmd_amount == 1)
		parse_command(&pars_data);
	else
		parser_loop(pars_data);
	(*data).parsed_lst = *pars_data.parsed_lst;
	ft_token_lstclear(tokens);
	return (1);
}
