/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:39:07 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/03 15:21:46 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_in_out_part_2(t_token *current, t_parsed **new)
{
	if (current->type == REDIR_OUT)
	{
		if (current->next)
		{
			(*new)->out_arr[(*new)->o_c] = ft_strdup(current->next->value);
			if (!(*new)->out_arr[(*new)->o_c++])
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
			(*new)->out_arr[(*new)->o_c] = ft_strdup(current->next->value);
			if (!(*new)->out_arr[(*new)->o_c++])
				return (2);
		}
		else
			return (0);
		(*new)->out_mode = OUT_MODE_FILE_APP;
	}
	return (1);
}

int	parse_in_out(t_token *current, t_parsed **new)
{
	if (current->type == REDIR_IN)
	{
		if (current->next)
		{
			(*new)->in_arr[(*new)->i_c] = ft_strdup(current->next->value);
			if (!(*new)->in_arr[(*new)->i_c++])
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
			(*new)->in_arr[(*new)->i_c] = ft_strdup(current->next->value);
			if (!(*new)->in_arr[(*new)->i_c++])
				return (2);
		}
		else
			return (0);
		(*new)->in_mode = IN_MODE_HERE_DOC;
	}
	return (parse_in_out_part_2(current, new));
}

void	clear_parsing(t_data *data)
{
	ft_token_lstclear(&data->token_lst);
	free_p_lst(&data->parsed_lst);
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
