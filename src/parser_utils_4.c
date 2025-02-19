/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:39:07 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/19 15:41:34 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	parse_in_out(t_token *current, t_parsed **new)
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
