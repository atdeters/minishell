// #include "parser.h"
#include "minishell.h"
/*
I also should take env_lst, becasue after parsind I will not know where should I put vatiables

Possbile shit with redirection:
cat < Makefile >> infile
< Makefile >>infile cat
>infile cat <Makefile
cat <some
< some cat
So cmd can be everywhere BUT after redirection sign it alway should be filename 
FUNNY/IMPORTANT: infile > cat1 ||->>> This will create file with name cat1

Example to work with:
wc < Makefile -w | >> infile cat | echo $user | cat ""

After lexing it will be:
type: 0, value: wc 
type: 5, value: (null)
type: 0, value: Makefile 
type: 0, value: -w 
type: 4, value: (null)
type: 8, value: (null)
type: 0, value: infile 
type: 0, value: cat 
type: 4, value: (null)
type: 0, value: echo 
type: 3, value: user 
type: 4, value: (null)
type: 0, value: cat 
type: 2, value: 

What i want to get: 
cmd_and_args = ["wc", "-w", NULL]
in = Makefile
in_mode = IN_MODE_FILE
out = PIPE
out_mode = OUT_MODE_PIPE
prew->NULL
next -> next

cmd_and_args = ["cat",  NULL]
in = PIPE
in_mode = IN_MODE_PIPE
out = infile
out_mode = OUT_MODE_FILE_APP
prew->prew
next -> next

cmd_and_args = ["echo", "{user=value}" NULL]
in = PIPE
in_mode = IN_MODE_PIPE
out = PIPE
out_mode = OUT_MODE_PIPE
prew->prew
next -> next

cmd_and_args = ["cat", "", NULL]
in = PIPE
in_mode = IN_MODE_PIPE
out = OUT_STD
out_mode = OUT_MODE_STD
prew->prew
next -> NULL
*/

/*
for the first call we assign the number of commands that we have
for example for the command: wc < Makefile -w | >> infile cat | echo $user | cat ""
we have 4 commands
than we call this function everythime when we parse new command and pass as argument 1
for the first node we pass 1 and expect in return 0. It means that we should redirect output 
to the pipefor second node we pass 1 again and expect in return 0. Same idea
Same for 3 node
And for last node because numb_of_cmd will be equal to numb_of_exec we will return 1
*/
// int		numb_of_exec(int	value)
// {
// 	static int numb_of_cmd = 0;
// 	static int numb_of_exec = 0;


// 	if (!numb_of_cmd)
// 	{
// 		numb_of_cmd = value;
// 		return (numb_of_exec);
// 	}
// 	numb_of_exec++;
// 	if (numb_of_cmd == numb_of_exec)
// 		return (1);
// 	else
// 		return (0);	
// }

// int	parse_command(t_token *head, t_token *tail, t_data *data)
// {
// 	t_token		*current;
// 	t_parsed	*new;
// 	static int numb_of_exec = 0;

// 	current = head;
// 	new = create_p_node(NULL, NULL, NULL);
// 	if (!tail)
// 		return (check_type(head, ft_token_lstlast(head), (*data).pipes_amount, &new));
// 	else if (numb_of_exec == 0)
// 		check_type(head, tail, 1, &new);
// 	else if (numb_of_exec < (*data).pipes_amount + 1 && numb_of_exec != 0)
// 		check_type(head, tail, 2, &new);
// 	else
// 		check_type(head, tail, 3, &new);
// 	while (current != tail->next)
// 	{
// 		printf("get into parse_command\n");
// 		if (current->type == REDIR_IN)
// 		{
// 			if (current->next)
// 			{
// 				new->in = ft_strdup(current->next->value);
// 				if (!new->in)
// 					return (2);
// 			}	
// 			else
// 				return (0);
// 			new->in_mode = IN_MODE_FILE;
// 		}
// 		// if (current->type == )
// 	}
// 	numb_of_exec++;
// 	return (1);
// }

// int	parser(t_token **tokens, t_data *data)
// {
// 	t_token *current;
// 	t_token *head;
// 	t_token *tail;

// 	current = *tokens;
// 	head = current;
// 	(*data).pipes_amount = pipe_counter(tokens);
// 	if ((*data).pipes_amount == 0)
// 		return (parse_command(head, NULL, data), 1);
// 	else 
// 	{
// 		while (current)
// 		{
// 			if (current->next && current->next->type == PIPE)
// 			{
// 				tail = current;
// 				parse_command(head, tail, data);
// 				current = current->next;
// 				head = current->next;
// 			}
// 			current = current->next;
// 		}
// 	}
// 	return (1);
// }

void	init_pars_data(t_pars_data *pars_data, t_data *data, t_token **tokens)
{
	(*pars_data).env_lst = &data->env_lst;
	(*pars_data).token_lst = tokens;
	(*pars_data).cmd_amount = pipe_counter(tokens) + 1;
	(*data).pipes_amount = pipe_counter(tokens);
	(*pars_data).parsed_amount = 0;
}

void	call_check_type(t_pars_data *pars_data, t_parsed *new)
{
	if (!(*pars_data).cur_tail)
		check_type((*pars_data).cur_head, ft_token_lstlast((*pars_data).cur_head),
		(*pars_data).cmd_amount, &new);
	else if ((*pars_data).parsed_amount == 0)
		check_type((*pars_data).cur_head, (*pars_data).cur_tail, 1, &new);
	else if ((*pars_data).parsed_amount < (*pars_data).cmd_amount &&
	 (*pars_data).parsed_amount != 0)
		check_type((*pars_data).cur_head, (*pars_data).cur_tail, 2, &new);
	else
		check_type((*pars_data).cur_head, (*pars_data).cur_tail, 3, &new);
}

int	parse_in_out_part_2(t_token *current, t_parsed **new)
{
	if (current->type == REDIR_OUT)
	{
		if (current->next)
		{
			(*new)->out = ft_strdup(current->next->value);
			if (!(*new)->out)
				return (2);
		}	
		else
			return (0);
			(*new)->out_mode = OUT_MODE_FILE_TR;
	}
	if (current->type == REDIR_APPEND)
	{
		if (current->next)
		{
			(*new)->out = ft_strdup(current->next->value);
			if (!(*new)->out)
				return (2);
		}	
		else
			return (0);
			(*new)->out_mode = OUT_MODE_FILE_APP;
	}
	return (1);
}

int parse_in_out(t_token *current, t_parsed **new)
{
	if (current->type == REDIR_IN)
	{
		if (current->next)
		{
			(*new)->in = ft_strdup(current->next->value);
			if (!(*new)->in)
				return (2);
		}	
		else
			return (0);
			(*new)->in_mode = IN_MODE_FILE;
	}
	if (current->type == DELIMITER)
	{
		if (current->next)
		{
			(*new)->in = ft_strdup(current->next->value);
			if (!(*new)->in)
				return (2);
		}	
		else
			return (0);
			(*new)->in_mode = IN_MODE_HERE_DOC;
	}
	return (parse_in_out_part_2(current, new));
}

int	parse_command(t_pars_data *pars_data)
{
	t_parsed	*new;
	t_token 	*current;
	t_token 	*prev;
	int			i;

	new = create_p_node(NULL, NULL, NULL);
	i = 0;
	call_check_type(pars_data, new);
	(*pars_data).parsed_amount++;
	current = (*pars_data).cur_head;
	prev = NULL;
	while (current != (*pars_data).cur_tail->next)
	{
		if (!parse_in_out(current, &new))
			return (0);
		if (current->type == WORD && prev && (prev->type != REDIR_APPEND && prev->type != REDIR_OUT && prev->type != REDIR_IN && prev->type != DELIMITER))
			i++;
		prev = current;
		current = current->next;
	}
	new->cmd_and_args = malloc(sizeof(char *) * (i + 1));
	if (!new->cmd_and_args)
		return (0);
	new->cmd_and_args[i] = NULL;
	current = (*pars_data).cur_head;
	i = 0;
	while (current)
	{
		if (current->type == WORD && prev && (prev->type != REDIR_APPEND  && prev->type != REDIR_OUT && prev->type != REDIR_IN && prev->type != DELIMITER))
		{
			new->cmd_and_args[i] = ft_strdup(current->value);
			if (!new->cmd_and_args[i])
				return (0);
			i++;
		}
		prev = current;
		current = current->next;
	}
	add_p_back((*pars_data).parsed_lst, new);
	return (1);
}

int	parser_loop(t_pars_data pars_data)
{
	t_token *current;

	current = *(pars_data.token_lst);
	while (current)
	{
		if ((current->next && current->next->type == PIPE) || !current->next)
		{
			pars_data.cur_tail = current;
			if (!parse_command(&pars_data))
				return (0);
			pars_data.cur_head = current->next;
		}
		current = current->next;
	}
	return (1);
}

int	parser_main(t_token **tokens, t_data *data)
{
	t_pars_data pars_data;

	init_pars_data(&pars_data, data, tokens);
	// printf("cmd_amount: %d\n", pars_data.cmd_amount);
	if (pars_data.cmd_amount == 1)
		parse_command(&pars_data);
	else
		parser_loop(pars_data);
	(*data).parsed_lst = *pars_data.parsed_lst;
	ft_token_lstclear(tokens);
	return (1);
}

// int	parser(t_token **tokens, t_env_lst **env_lst, t_parsed **parsed, int *amount_of_pipes)
// {
// 	t_token *current;
// 	t_token *head;
// 	t_token *tail;

// 	current = *tokens;
// 	head = current;
// 	*amount_of_pipes = pipe_counter(tokens);
// 	if (*amount_of_pipes == 0)
// 		return (parse_command(head, NULL, env_lst, parsed), 1);
// 	else 
// 	{
// 		while (current)
// 		{
// 			if (current->next && current->next->type == PIPE)
// 			{
// 				tail = current;
// 				parse_command(head, tail, env_lst, parsed);
// 				current = current->next;
// 				head = current->next;
// 			}
// 			current = current->next;
// 		}
// 	}
// 	return (1);
// }
