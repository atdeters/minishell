/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:59:25 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/22 20:08:41 by adeters          ###   ########.fr       */
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

// should i really exit? I should add here return 0 instead
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

char	*return_from_env_with_data(t_data *data, char *field)
{
	t_env_lst	*tmp;
	char		*res;

	res = NULL;
	tmp = data->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->filed, field, ft_strlen(field)) == 0)
		{
			res = ft_strdup(tmp->value);
			if (!res)
				return (NULL);
			return (res);
		}
		tmp = tmp->next;
	}
	res = malloc(sizeof(char));
	res[0] = '\0';
	return (res);
}

//Return 1 if funct found and deleted node otherwise = 0
int	del_env_var(t_env_lst *lst, char *field)
{
	t_env_lst	*prev;
	t_env_lst	*tmp;

	tmp = lst;
	while (tmp && ft_strncmp(tmp->value, field, ft_strlen(field) != 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (ft_strncmp(tmp->value, field, ft_strlen(field) == 0))
	{
		prev->next = tmp->next;
		ft_env_lstdelone(tmp);
		return (1);
	}
	return (0);
}
