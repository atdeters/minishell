/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:30 by vsenniko          #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// shoud rewrite in and ount mode after this function call
t_parsed	*create_p_node(char **cmd_and_args, char *in, char *out)
{
	t_parsed	*new;

	(void)cmd_and_args;
	(void)in;
	(void)out;
	new = malloc(sizeof(t_parsed));
	if (!new)
		return (NULL);
	new->cmd_and_args = NULL;
	new->in_mode = 0;
	new->out_mode = 0;
	new->in_arr = NULL;
	new->out_arr = NULL;
	new->i_c = 0;
	new->o_c = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

static t_parsed	*get_p_last(t_parsed *lst)
{
	t_parsed	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	add_p_back(t_parsed **lst, t_parsed *new)
{
	t_parsed	*last;

	if (!new)
		return ;
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = get_p_last(*lst);
	last->next = new;
	new->prev = last;
}

void	free_p_node(t_parsed *node)
{
	int	i;

	i = 0;
	if (node->cmd_and_args)
	{
		while (node->cmd_and_args[i])
			free(node->cmd_and_args[i++]);
		free(node->cmd_and_args);
	}
	i = 0;
	if (node->in_arr)
	{
		while (node->in_arr[i])
			free(node->in_arr[i++]);
		free(node->in_arr);
	}
	i = 0;
	if (node->out_arr)
	{
		while (node->out_arr[i])
			free(node->out_arr[i++]);
		free(node->out_arr);
	}
	free(node);
}

void	free_p_lst(t_parsed **lst)
{
	t_parsed	*current;
	t_parsed	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		free_p_node(tmp);
	}
	*lst = NULL;
}
