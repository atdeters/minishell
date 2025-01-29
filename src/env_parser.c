/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:59:25 by vsenniko          #+#    #+#             */
/*   Updated: 2025/01/29 14:28:45 by vsenniko         ###   ########.fr       */
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

static void	transfer_into_node(char *str, t_data *data, int j)
{
	char		*field;
	char		*value;
	t_env_lst	*node;

	field = ft_substr(str, 0, j);
	if (!field)
		error_exit(NULL, NULL, data->env_lst, 1);
	value = ft_substr(str, j + 1, ft_strlen(str) - j);
	if (!value)
		error_exit(field, NULL, data->env_lst, 1);
	node = ft_env_lstnew(field, value);
	if (!node)
		error_exit(field, value, data->env_lst, 1);
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

// int	main(int argc, char **argv, char **env)
// {
// 	t_data		data;
// 	t_env_lst	*node;

// 	(void)argc;
// 	(void)argv;
// 	if (init_shell(&data))
// 		return (p_err(INIT));
// 	parse_env(&data, env);
// 	node = data.env_lst;
// 	while (node)
// 	{
// 		printf("%s=%s\n", node->filed, node->value);
// 		node = node->next;
// 	}
// 	ft_env_lstclear(&data.env_lst);
// }
