/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:39:07 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/21 20:00:02 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

staitc int	parse_out_redir(t_token *current, t_parsed **new, t_data *data)
{
	(*new)->out_arr[(*new)->o_c] = ft_strdup(current->next->value);
	if (!(*new)->out_arr[(*new)->o_c])
		return (data->error = ERR_MALLOC, 0);
	(*new)->o_c++;
	return (1);
}

static int	parse_in_redir(t_token *current, t_parsed **new, t_data *data)
{
	(*new)->in_arr[(*new)->i_c] = ft_strdup(current->next->value);
	if (!(*new)->in_arr[(*new)->i_c])
		return (data->error = ERR_MALLOC, 0);
	(*new)->i_c++;
	return (1);
}

int	parse_in_out_part_2(t_token *current, t_parsed **new, t_data *data)
{
	if (current->type == REDIR_OUT)
	{
		if (current->next)
			return (parse_out_redir(current, new, data));
		else
			return (1);
		(*new)->out_mode = OUT_MODE_FILE_TR;
	}
	if (current->type == REDIR_APPEND)
	{
		if (current->next)
			return (parse_out_redir(current, new, data));
		else
			return (1);
		(*new)->out_mode = OUT_MODE_FILE_APP;
	}
	return (1);
}

int	parse_in_out(t_token *current, t_parsed **new, t_data *data)
{
	if (current->type == REDIR_IN)
	{
		if (current->next)
			return (parse_in_redir(current, new, data));
		else
			return (1);
		(*new)->in_mode = IN_MODE_FILE;
	}
	if (current->type == DELIMITER)
	{
		if (current->next)
			return (parse_in_redir(current, new, data));
		else
			return (1);
		(*new)->in_mode = IN_MODE_HERE_DOC;
	}
	return (parse_in_out_part_2(current, new, data));
}

// void	clear_parsing(t_data *data)
// {
// 	ft_token_lstclear(&data->token_lst);
// 	free_p_lst(&data->parsed_lst);
// }
