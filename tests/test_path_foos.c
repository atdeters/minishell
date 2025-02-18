/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pathstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:58:13 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 17:37:36 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// TEST COMMANDS FOR THE add_path FUNCTION
// #define COMMAND "cat Makefile"
// #define COMMAND ""
// #define COMMAND "caat Makefile"
#define COMMAND "funcheck ./mini"
// #define COMMAND NULL

int	main(int ac, char **av, char **env)
{
	t_data data;
	
	if (init_shell(&data, env))
		return (pc_err(data.error));
	(void)ac;
	(void)av;
	parse_env(&data, env);

	// TEST: getting the pathstr
	char *pathstr;

	pathstr = get_pathstr(&data);
	printf("%s\n\n\n", pathstr);


	// TEST: checking if add_path works as intended
	char **command = ft_split(COMMAND, ' ');
	if (!command)
	{
		printf("ft_split didn't work in the test main!\n");
		return (1);
	}
	add_path(&data, command);
	int i = 0;
	if (!command[i])
	{
		printf("add path failed somewhere\n");
		return (1);
	}
	while (command[i])
	{
		printf("%s\n", command[i]);
		i++;
	}
}