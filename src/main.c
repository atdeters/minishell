/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 19:44:14 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(t_data *data, int fd_in, int fd_out)
{
	if (fd_in != 0 && dup2(data->fd[data->next_pipe][0], STDIN_FILENO) == -1)
		return (0);
	if (fd_out != 1 && dup2(data->fd[data->next_pipe][1], STDOUT_FILENO) == -1)
		return (0);
	if (data->fd[data->next_pipe][0] != -1)
		close (data->fd[data->next_pipe][0]);
	if (data->fd[data->next_pipe][1] != -1)
		close (data->fd[data->next_pipe][1]);
	data->next_pipe++;
}

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