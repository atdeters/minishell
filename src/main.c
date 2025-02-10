/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/10 16:34:17 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;

	if (init_shell(&data))
		return (p_err(INIT));
	while (true)
	{
		data.input = get_input(&data);
		if (data.input && !ft_strncmp(data.input, "clear", 5))
			clear();
		else if (data.input && !ft_strncmp(data.input, "pwd", 3))
			pwd();
		free(data.input);
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