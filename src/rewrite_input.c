/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:16:04 by vsenniko          #+#    #+#             */
/*   Updated: 2025/03/21 20:06:56 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_special(char **word, char **res, char **start_w,
		t_data *data)
{
	if (ft_strlen(*res) == 1 && *res[0] == '$')
	{
		if (!special_case_pid(word))
			return (free(*start_w), free(*res), data->error = ERR_MALLOC, 0);
	}
	else if (ft_strlen(*res) == 1 && *res[0] == '?')
	{
		*word = ft_itoa(data->exit_status);
		if (!*word)
			return (free(*start_w), free(*res), data->error = ERR_MALLOC, 0);
	}
	else
	{
		*word = return_from_env_with_data(data, *res);
		if (!*word)
			return (free(*start_w), free(*res), data->error = ERR_MALLOC, 0);
	}
	return (1);
}

static int	sub_replace(t_data *data, int start, int finish, char **input)
{
	char	*start_w;
	char	*word;
	char	*res;

	start_w = ft_substr(*input, 0, start);
	if (!start_w)
		return (data->error = ERR_MALLOC, 0);
	res = ft_substr(*input, start + 1, finish - start);
	if (!res)
		return (free(start_w), data->error = ERR_MALLOC, 0);
	if (!check_for_special(&word, &res, &start_w, data))
		return (0);
	free(res);
	res = ft_strjoin(start_w, word);
	if (!res)
		return (free(start_w), free(word), data->error = ERR_MALLOC, 0);
	free(start_w);
	free(word);
	word = ft_substr(*input, finish + 1, ft_strlen(*input) - finish);
	if (!word)
		return (free(res), data->error = ERR_MALLOC, 0);
	start_w = ft_strjoin(res, word);
	if (!start_w)
		return (free(word), free(res), data->error = ERR_MALLOC, 0);
	return (free(*input), free(word), free(res), *input = start_w, 1);
}

static int	replace_word(t_data *data, char **input)
{
	int	i;
	int	start;

	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '$' && !in_single_qoute(i, *input))
		{
			start = i;
			if ((*input)[i + 1] && ((*input)[i + 1] == '$'
					|| (*input)[i + 1] == '?'))
				return (sub_replace(data, start, i + 1, input));
			while ((*input)[i] && (*input)[i + 1]
				&& ft_isalnum((*input)[i + 1]))
				i++;
			if (start != i)
				return (sub_replace(data, start, i, input));
		}
		if ((*input)[i])
			i++;
	}
	return (1);
}

int	expand_env_var(t_data *data, char **input)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '$')
			counter++;
		i++;
	}
	i = 0;
	while (i != counter)
	{
		if (!replace_word(data, input))
			return (0);
		i++;
	}
	return (1);
}

int	check_replace_input(t_data *data)
{
	int	i;

	if (pipe_problem(data))
		return (0);
	if (quotes_problem(data))
		return (0);
	i = expand_env_var(data, &data->input);
	if (data->error == ERR_MALLOC)
		rage_quit(data, data->error = ERR_MALLOC, true, NULL);
	return (i);
}
