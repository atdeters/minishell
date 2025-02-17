/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:59 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/17 17:09:38 by vsenniko         ###   ########.fr       */
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

void	init_pars_data(t_pars_data *pars_data, t_data *data, t_token **tokens)
{
	(*pars_data).env_lst = &data->env_lst;
	(*pars_data).token_lst = tokens;
	(*pars_data).cmd_amount = pipe_counter(tokens) + 1;
	(*data).pipes_amount = pipe_counter(tokens);
	(*pars_data).parsed_amount = 0;
	*(*pars_data).parsed_lst = NULL;
}

void	call_check_type(t_pars_data *pars_data, t_parsed *new)
{
	if (!(*pars_data).cur_tail)
		check_type((*pars_data).cur_head, ft_token_lstlast((*pars_data).cur_head),
		(*pars_data).cmd_amount, &new);
	else if ((*pars_data).parsed_amount == 0)
		check_type((*pars_data).cur_head, (*pars_data).cur_tail, 1, &new);
	else if ((*pars_data).parsed_amount < (*pars_data).cmd_amount &&
	 (*pars_data).parsed_amount != 0)
		check_type((*pars_data).cur_head, (*pars_data).cur_tail, 2, &new);
	else
		check_type((*pars_data).cur_head, (*pars_data).cur_tail, 3, &new);
}

int	parse_in_out_part_2(t_token *current, t_parsed **new)
{
	if (current->type == REDIR_OUT)
	{
		if (current->next)
		{
			(*new)->out = ft_strdup(current->next->value);
			if (!(*new)->out)
				return (2);
		}	
		else
			return (0);
		(*new)->out_mode = OUT_MODE_FILE_TR;
	}
	if (current->type == REDIR_APPEND)
	{
		if (current->next)
		{
			(*new)->out = ft_strdup(current->next->value);
			if (!(*new)->out)
				return (2);
		}	
		else
			return (0);
		(*new)->out_mode = OUT_MODE_FILE_APP;
	}
	return (1);
}

int parse_in_out(t_token *current, t_parsed **new)
{
	if (current->type == REDIR_IN)
	{
		if (current->next)
		{
			(*new)->in = ft_strdup(current->next->value);
			if (!(*new)->in)
				return (2);
		}	
		else
			return (0);
		(*new)->in_mode = IN_MODE_FILE;
	}
	if (current->type == DELIMITER)
	{
		if (current->next)
		{
			(*new)->in = ft_strdup(current->next->value);
			if (!(*new)->in)
				return (2);
		}	
		else
			return (0);
		(*new)->in_mode = IN_MODE_HERE_DOC;
	}
	return (parse_in_out_part_2(current, new));
}

char *return_from_env(t_pars_data pars_data, char *field)
{
	t_env_lst *tmp;
	char	*res;

	res = NULL;
	tmp = *pars_data.env_lst;
	while(tmp)
	{
		if (ft_strncmp(tmp->filed, field, ft_strlen(field) - 1) == 0)
		{
			res = ft_strdup(tmp->value);
			return (res);
		}
		tmp = tmp->next;
	}
	res = malloc(sizeof(char));
	res[0] = '\0';
	return (res);
}

int	parse_command(t_pars_data *pars_data)
{
	t_parsed	*new;
	t_token 	*current;
	t_token 	*prev;
	int			i;

	new = create_p_node(NULL, NULL, NULL);
	i = 0;
	call_check_type(pars_data, new);
	(*pars_data).parsed_amount++;
	current = (*pars_data).cur_head;
	prev = NULL;
	while (current && current != (*pars_data).cur_tail->next)
	{
		if (!parse_in_out(current, &new))
			return (0);
		if ((current->type == WORD || current->type ==DOUBLE_QOUTE || current->type ==DOLAR_SIGN || current->type ==SINGLE_QOUTE) && (!prev || (prev && (prev->type != REDIR_APPEND && prev->type != REDIR_OUT && prev->type != REDIR_IN && prev->type != DELIMITER))))
			i++;
		prev = current;
		current = current->next;
	}
	new->cmd_and_args = malloc(sizeof(char *) * (i + 1));
	if (!new->cmd_and_args)
		return (0);
	new->cmd_and_args[i] = NULL;
	current = (*pars_data).cur_head;
	i = 0;
	while (current && current != (*pars_data).cur_tail->next)
	{
		if ((current->type == WORD || current->type ==DOUBLE_QOUTE || current->type ==SINGLE_QOUTE) && (!prev || (prev && (prev->type != REDIR_APPEND && prev->type != REDIR_OUT && prev->type != REDIR_IN && prev->type != DELIMITER))))
		{
			new->cmd_and_args[i] = ft_strdup(current->value);
			if (!new->cmd_and_args[i])
				return (0);
			i++;
		}
		else if (current->type == DOLAR_SIGN && (!prev || (prev && (prev->type != REDIR_APPEND && prev->type != REDIR_OUT && prev->type != REDIR_IN && prev->type != DELIMITER))))
		{
			new->cmd_and_args[i] = return_from_env(*pars_data, current->value);
			i++;
		}
		prev = current;
		current = current->next;
	}
	add_p_back((*pars_data).parsed_lst, new);
	return (1);
}

int	parser_loop(t_pars_data pars_data)
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
