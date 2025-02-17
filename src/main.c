/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
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
// int main()
// {
// 	t_token *lst;

// 	lst = NULL;
// 	char *msg = "ls|cat -e<<her_doc>file1>>file2";
// 	lexing(msg, &lst);
// 	while (lst)
// 	{
// 		printf("type: %d, value: %s\n", lst->type, lst->value);
// 		lst = lst->next;
// 	}
// }