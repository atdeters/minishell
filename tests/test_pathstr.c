/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:58:13 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 17:08:06 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*get_pathstr(t_data *data)
{
	while (data->env_lst)
	{
		if (!ft_strncmp(data->env_lst->filed, "PATH",
				ft_strlen(data->env_lst->filed)))
			return (data->env_lst->value);
		data->env_lst = data->env_lst->next;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	if (init_shell(&data, env))
		return (pc_err(data.error));
	(void)ac;
	(void)av;
	parse_env(&data, env);

	char *pathstr;

	pathstr = get_pathstr(&data);
	printf("%s\n", pathstr);
}