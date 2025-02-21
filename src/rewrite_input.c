/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:16:04 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/21 15:21:02 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_case_pid(char **word)
{
	char	*res;
	int		pid;

	pid = getpid();
	res = ft_itoa(pid);
	if (!res)
		return (0);
	*word = res;
	return (1);
}

static int	check_for_special(char **word, char **res, char **start_w,
		t_data *data)
{
	if (ft_strlen(*res) == 1 && *res[0] == '$')
	{
		if (!special_case_pid(word))
			return (free(*start_w), free(*res), 0);
	}
	else
	{
		*word = return_from_env_with_data(data, *res);
		if (!*word)
			return (free(*start_w), free(*res), 0);
	}
	return (1);
}

static int	sub_replace(t_data *data, int start, int finish)
{
	char	*start_w;
	char	*word;
	char	*res;

	start_w = ft_substr(data->input, 0, start);
	if (!start_w)
		return (0);
	res = ft_substr(data->input, start + 1, finish - start);
	if (!res)
		return (free(start_w), 0);
	if (!check_for_special(&word, &res, &start_w, data))
		return (0);
	free(res);
	res = ft_strjoin(start_w, word);
	if (!res)
		return (free(start_w), free(word), 0);
	free(start_w);
	free(word);
	word = ft_substr(data->input, finish + 1, ft_strlen(data->input) - finish);
	if (!word)
		return (free(res), 0);
	start_w = ft_strjoin(res, word);
	if (!start_w)
		return (free(word), free(res), 0);
	return (free(data->input), free(word), free(res), data->input = start_w, 1);
}

static int	replace_word(t_data *data)
{
	int	i;
	int	start;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '$')
		{
			start = i;
			if (data->input[i + 1] && data->input[i + 1] == '$')
				return (sub_replace(data, start, i + 1));
			while (data->input[i] && data->input[i + 1]
				&& ft_isalnum(data->input[i + 1]))
				i++;
			return (sub_replace(data, start, i));
		}
		if (data->input[i])
			i++;
	}
	return (1);
}

int	check_replace_input(t_data *data)
{
	while (ft_strnstr(data->input, "$", ft_strlen(data->input)))
	{
		if (!replace_word(data))
			return (0);
	}
	return (1);
}
