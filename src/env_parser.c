/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:59:25 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/20 19:44:33 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_exit_env(char *f, char *v, t_env_lst *lst, int exit_code)
{
	if (f)
		free(f);
	if (v)
		free(v);
	if (lst)
		ft_env_lstclear(&lst);
	exit(exit_code);
}

//should i really exit? I should add here return 0 instead
static void	transfer_into_node(char *str, t_data *data, int j)
{
	char		*field;
	char		*value;
	t_env_lst	*node;

	field = ft_substr(str, 0, j);
	if (!field)
		error_exit_env(NULL, NULL, data->env_lst, 1);
	value = ft_substr(str, j + 1, ft_strlen(str) - j);
	if (!value)
		error_exit_env(field, NULL, data->env_lst, 1);
	node = ft_env_lstnew(field, value);
	if (!node)
		error_exit_env(field, value, data->env_lst, 1);
	if (!data->env_lst)
		data->env_lst = node;
	else
		ft_env_lstadd_back(&data->env_lst, node);
}

void	parse_env(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				transfer_into_node(env[i], data, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	check_replace_input(t_data *data)
{
	int	i;
	int	start;
	char	*word;
	char	*n_input;
	char	*res;
	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '$')
		{
			start = i;
			while (data->input[i] && !ft_is_space(data->input[i]))
				i++;
			word = ft_substr(data->input, start, i - start);
			if (!word)
				return (0);
			n_input = ft_substr(data->input, 0, start);
			if (!n_input)
				return (free(word), 0);
			res = ft_strjoin(n_input, word);
			free(n_input);
			free(word);
			start = i;
			while (data->input[start])
				start++;
			//??
		}
		if (data->input[i])
			i++;
	}
}
