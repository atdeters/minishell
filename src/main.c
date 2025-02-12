/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/12 14:54:00 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data, int fd_in, int fd_out, char **command)
{
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (p_err(FORK));
	if (data->pid[data->n_pid] == 0)
	{
		if (cool_dup(data, fd_in, fd_out))
			return (p_err(DUP));
		if (execve(command[0], command, data->envp) == -1)
			exit(p_err(EXEC));
	}
	data->n_pid++;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	char *com[] = { "/usr/bin/cat", NULL };
	data.envp = env;

	if (init_shell(&data))
		return (p_err(INIT_PROG));
	while (true)
	{
		if (init_command(&data))
			return (p_err(INIT_COM));
		data.input = get_input(&data);
		if (data.input && !ft_strncmp(data.input, "clear", 5))
			clear();
		else if (data.input && !ft_strncmp(data.input, "pwd", 3))
			pwd();

		data.pipes_amount = 1;
		data.fd[0][0] = open("Makefile", O_RDONLY);
		data.fd[0][1] = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0644);
		execute(&data, data.fd[0][0], data.fd[0][1], com);
		close_all(&data);
		wait_all(&data);

		free(data.input);
	}
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