/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:47:41 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/22 19:06:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arr_size(t_data *data)
{
	int			i;
	t_env_lst	*tmp;

	i = 0;
	tmp = data->env_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	*join_from_node(t_env_lst *cur)
{
	char	*f_word;
	char	*res;

	f_word = ft_strjoin(cur->filed, "=");
	if (!f_word)
		return (NULL);
	res = ft_strjoin(f_word, cur->value);
	if (!res)
		return (free(f_word), NULL);
	free(f_word);
	return (res);
}

void	free_two_dim(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// Return 1 in case of success, otherwise 0
int	parser_env_into_arr(t_data *data)
{
	char		**res;
	t_env_lst	*tmp;
	int			i;

	i = 0;
	res = ft_calloc((count_arr_size(data) + 1), sizeof(char *));
	if (!res)
		return (0);
	tmp = data->env_lst;
	while (tmp)
	{
		res[i] = join_from_node(tmp);
		if (!res[i])
			return (free_two_dim(res), 0);
		i++;
		tmp = tmp->next;
	}
	data->envp = res;
	return (1);
}
