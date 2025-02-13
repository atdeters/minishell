/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:56:57 by adeters           #+#    #+#             */
/*   Updated: 2025/02/13 20:19:15 by adeters          ###   ########.fr       */
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

int	execute(t_data *data, int fd_in, int fd_out, char **command)
{
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (pc_err(ERR_FORK));
	if (data->pid[data->n_pid] == 0)
	{
		if (cool_dup(data, fd_in, fd_out))
			return (pc_err(ERR_DUP2));
		if (execve(command[0], command, data->envp) == -1)
			exit(pc_err(ERR_EXECVE));
	}
	data->n_pid++;
	return (0);
}

int	write_hst_file(t_data *data, char *hist_file_path)
{
	int		fd;
	t_list	*pre;

	if (!hist_file_path)
		return (setnret(data, ERR_HIST_WFILE));
	fd = open(hist_file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return (setnret(data, ERR_HIST_WFILE));
	while (data->sess_hist_lst && data->sess_hist_lst->next)
	{
		write(fd, data->sess_hist_lst->content, ft_strlen(data->sess_hist_lst->content));
		free(data->sess_hist_lst->content);
		write(fd, "\n", 1);
		pre = data->sess_hist_lst;
		data->sess_hist_lst = data->sess_hist_lst->next;
		free (pre);
	}
	if (data->sess_hist_lst)
	{
		write(fd, data->sess_hist_lst->content, ft_strlen(data->sess_hist_lst->content));
		free(data->sess_hist_lst->content);
		free (data->sess_hist_lst);
	}
	return (0);
}

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
				clear();
			else if (data.input && !ft_strncmp(data.input, "pwd", 3))
				pwd();
			else if (data.input && !ft_strncmp(data.input, "exit", 4))
			{
				free(data.input);
				break;
			}
			
			// char *com[] = { "/usr/bin/cat", NULL };
			// data.pipes_amount = 1;
			// data.fd[0][0] = open("Makefile", O_RDONLY);
			// data.fd[0][1] = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0644);
			// execute(&data, data.fd[0][0], data.fd[0][1], com);
			// close_all(&data);
			// wait_all(&data);
			
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