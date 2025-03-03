/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:50 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/03 15:12:43 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_type_in(t_token *head, t_token *tail, t_parsed **new,
		int flag)
{
	t_token	*current;

	current = head;
	while (current && current != tail->next)
	{
		if (current->type == REDIR_IN)
			(*new)->in_mode = IN_MODE_FILE;
		else if (current->type == DELIMITER)
			(*new)->in_mode = IN_MODE_HERE_DOC;
		if ((*new)->in_mode == 0)
		{
			if (flag == 2 || flag == 3)
				(*new)->in_mode = IN_MODE_PIPE;
			else
				(*new)->in_mode = IN_MODE_STD;
		}
		current = current->next;
	}
}

static void	check_type_out(t_token *head, t_token *tail, t_parsed **new,
		int flag)
{
	t_token	*current;

	current = head;
	while (current && current != tail->next)
	{
		if (current->type == REDIR_OUT)
			(*new)->out_mode = OUT_MODE_FILE_TR;
		else if (current->type == REDIR_APPEND)
			(*new)->out_mode = OUT_MODE_FILE_APP;
		if ((*new)->out_mode == 0)
		{
			if (flag == 1 || flag == 2)
				(*new)->out_mode = OUT_MODE_PIPE;
			else
				(*new)->out_mode = OUT_MODE_STD;
		}
		current = current->next;
	}
}

/*
FLAGS:
0 = IN = STDIN, OUT = STDOUT
1 -> IN = STDIN, OUT = PIPE
2 -> IN = PIPE, OUT = PIPE
3 -> IN PIPE, OUT = STDOUT
*/
static void	check_type(t_token *head, t_token *tail, int flag, t_parsed **new)
{
	check_type_in(head, tail, new, flag);
	check_type_out(head, tail, new, flag);
}

static int	count_size(t_token *head, t_token *tail, t_parsed *new)
{
	t_token	*tmp;
	int		in_count;
	int		out_count;

	in_count = 0;
	out_count = 0;
	tmp = head;
	while (tmp != tail->next)
	{
		if (tmp->type == REDIR_IN)
			in_count++;
		if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			out_count++;
		tmp = tmp->next;
	}
	new->in_arr = malloc(sizeof(char *) * (in_count + 1));
	if (!new->in_arr)
		return (0);
	new->in_arr[in_count] = NULL;
	new->out_arr = malloc(sizeof(char *) * (out_count + 1));
	if (!new->out_arr)
		return (0);
	return (new->out_arr[out_count] = NULL, 1);
}

int	call_check_type(t_pars_data *pars_data, t_parsed *new)
{
	if (!count_size(pars_data->cur_head, pars_data->cur_tail, new))
		return (0);
	if (pars_data->cmd_amount == 1)
		check_type(pars_data->cur_head, ft_token_lstlast(pars_data->cur_head),
			0, &new);
	else if (pars_data->parsed_amount == 0 && pars_data->cmd_amount != 1)
		check_type(pars_data->cur_head, pars_data->cur_tail, 1, &new);
	else if (pars_data->parsed_amount < pars_data->cmd_amount - 1
		&& pars_data->parsed_amount != 0)
		check_type(pars_data->cur_head, pars_data->cur_tail, 2, &new);
	else
		check_type(pars_data->cur_head, pars_data->cur_tail, 3, &new);
	return (1);
}
