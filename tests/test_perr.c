/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_perr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:43:42 by adeters           #+#    #+#             */
/*   Updated: 2025/02/19 18:12:21 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// TEST CMDS TO UNCOMMENT
#define COMMAND "cat Makefile | cat -e"
// #define COMMAND "ls -l | echo $PATH | cat>> file2 | echo '$$smt $' | cat < infile | cat \"\""
// #define COMMAND "wc  <Makefile -w | >> infile cat | echo $SHELL | cat \"\" | ls -l -a"

char *rep_space(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == ' ')
			str[i] = '\0';
		i++;
	}
	return (str);
}

int main(int ac, char **av, char **env)
{
	t_data data;
	t_token *t_lst;

	if (init_shell(&data, env))
		return (pc_err(data.error));
	(void) ac;
	(void) av;

	t_lst = NULL;
	char *msg = COMMAND;
	data.parsed_lst = NULL; // Do in init_com
	lexing(msg, &t_lst); // Do in init_com
	parse_env(&data, env); // Do in init_shell
	parser_main(&t_lst, &data);
	while (data.parsed_lst)
	{
		execute(&data);
		data.parsed_lst = data.parsed_lst->next;
	}
	wait_all(&data);
	close_all(&data);
}