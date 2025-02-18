/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 19:28:25 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// write to pipe: fd[n_pipe][1]
// read from pipe: fd[n_pipe][0] -> then n_pipe++;
// Function that read from pipe uses fd[n_pipe][0] and then increases n_pipe
// Function that write to pipe uses fd[n_pipe][1] but doesn't increase n_pipe

// About the two fd arrays: The maximum amount of fds in a command can be 
// FD_LIMIT. So to check how many files can be opened we need to calculate the
// amount of pipes. So FD_LIMIT - (pipes_amount * 2) will give us the max. 
// number of files that can be opened with the remaining file descriptors

int	main(int ac, char **av, char **env)
{
	t_data			data;

	if (init_shell(&data, env))
		return (pc_err(data.error));
	while (true)
	{
		if (init_command(&data))
			pnc_err(&data);
		if (data.init_com_fails == 0)
		{
			data.input = get_input(&data);
			if (add_full_history(&data))
				pnc_err(&data);
			if (data.input && !ft_strncmp(data.input, "clear", 5))
				ft_clear();
			else if (data.input && !ft_strncmp(data.input, "pwd", 3))
				ft_pwd();
			else if (data.input && !ft_strncmp(data.input, "exit", 4))
			{
				free(data.input);
				break;
			}
			free(data.input);
		}
		if (data.init_com_fails >= MAX_INIT_COM_FAILS)
			return (pc_err(ERR_INIT_COM));
	}
	write_hst_file(&data, HIST_FILE_PATH);
}

/*
TEST CMDS:
ls|cat -e<<her_doc>file1>>file2
ls -l | echo $path | cat>> file2 | echo '$$smt $' | cat < infile | cat \"\"
*/
// int main(int ac, char **av, char **env)
// {
// 	t_data data;
// 	t_token *t_lst;

// 	if (init_shell(&data, env))
// 		return (pc_err(data.error));
// 	(void) ac;
// 	(void) av;

// 	t_lst = NULL;
// 	char *msg = "wc  Makefile -w | >> infile cat | echo $SHELL | cat \"\" | ls -l -a";
// 	data.parsed_lst = NULL;
// 	lexing(msg, &t_lst);
// 	parse_env(&data, env);
// 	t_token *tmp = t_lst;
// 	while (tmp)
// 	{
// 		printf("Value = %s, type = %d\n", tmp->value, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	printf("\n\n\n");
// 	parser_main(&t_lst, &data);
// 	while (data.parsed_lst)
// 	{
// 		int i = 0;
// 		while (data.parsed_lst->cmd_and_args[i])
// 		{
// 			printf("cmd_and_args[%d]: %s\n", i, data.parsed_lst->cmd_and_args[i]);
// 			i++;
// 		}
// 		printf("cmd_and_args[%d] = %s\n", i, data.parsed_lst->cmd_and_args[i]);
// 		printf("in: %s\n", data.parsed_lst->in);
// 		printf("out: %s\n", data.parsed_lst->out);
// 		printf("in_mode: %d\n", data.parsed_lst->in_mode);
// 		printf("out_mode: %d\n", data.parsed_lst->out_mode);
// 		printf("\n\n\n");
// 		data.parsed_lst = data.parsed_lst->next;
// 	}
// 	// parser_main(&t_lst, &data);
// 	// parser(t_lst, &data);
// 	// data->env_lst = 
// 	// while (lst)
// 	// {
// 	// 	printf("type: %d, value: %s\n", lst->type, lst->value);
// 	// 	lst = lst->next;
// 	// }
// }