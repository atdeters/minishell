/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parser_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:41:13 by adeters           #+#    #+#             */
/*   Updated: 2025/02/18 16:42:01 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEST CMDS TO UNCOMMENT
#define COMMAND "ls|cat -e<<her_doc>file1>>file2"
// #define COMMAND "ls -l | echo $PATH | cat>> file2 | echo '$$smt $' | cat < infile | cat \"\""
// #define COMMAND "wc  <Makefile -w | >> infile cat | echo $SHELL | cat \"\" | ls -l -a"

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
	data.parsed_lst = NULL;
	lexing(msg, &t_lst);
	parse_env(&data, env);
	t_token *tmp = t_lst;
	while (tmp)
	{
		printf("Value = %s, type = %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	printf("\n\n\n");
	parser_main(&t_lst, &data);
	while (data.parsed_lst)
	{
		int i = 0;
		while (data.parsed_lst->cmd_and_args[i])
		{
			printf("cmd_and_args[%d]: %s\n", i, data.parsed_lst->cmd_and_args[i]);
			i++;
		}
		printf("cmd_and_args[%d] = %s\n", i, data.parsed_lst->cmd_and_args[i]);
		printf("in: %s\n", data.parsed_lst->in);
		printf("out: %s\n", data.parsed_lst->out);
		printf("in_mode: %d\n", data.parsed_lst->in_mode);
		printf("out_mode: %d\n", data.parsed_lst->out_mode);
		printf("\n\n\n");
		data.parsed_lst = data.parsed_lst->next;
	}
}
