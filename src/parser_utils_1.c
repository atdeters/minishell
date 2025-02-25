/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:30 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/25 15:53:08 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// shoud rewrite in and ount mode after this function call
t_parsed	*create_p_node(char **cmd_and_args, char *in, char *out)
{
	t_parsed	*new;

	(void) cmd_and_args;
	(void) in;
	(void) out;
	new = malloc(sizeof(t_parsed));
	if (!new)
		return (NULL);
	new->cmd_and_args = NULL;
	new->in = NULL;
	new->out = NULL;
	new->in_mode = 0;
	new->out_mode = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_parsed	*get_p_last(t_parsed *lst)
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
	if (!node)
		return ;
	if (node->cmd_and_args)
	{
		while (node->cmd_and_args[i])
			free(node->cmd_and_args[i++]);
		free(node->cmd_and_args);
	}
	free(node->in);
	free(node->out);
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

int	pipe_counter(t_token **tokens)
{
	t_token	*current;
	int		pipe_count;

	current = *tokens;
	pipe_count = 0;
	while (current)
	{
		if (current->type == PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count);
}
