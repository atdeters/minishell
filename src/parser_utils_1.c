#include "minishell.h"
//shoud rewrite in and ount mode after this function call
t_parsed	*create_p_node(char **cmd_and_args, char *in, char *out)
{
	t_parsed	*new;

	new = malloc(sizeof(t_parsed));
	if (!new)
		return (NULL);
	new->cmd_and_args = cmd_and_args;
	new->in = in;
	new->out = out;
	new->in_mode = 0;
	new->out_mode = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_parsed	*get_p_last(t_parsed *lst)
{
	t_parsed *last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

t_parsed	*add_p_back(t_parsed **lst, t_parsed *new)
{
	t_parsed *last;

	if (!new)
		return (NULL);
	if (!*lst)
	{
		*lst = new;
		return (new);
	}
	last = get_p_last(*lst);
	last->next = new;
	new->prev = last;
	return (new);
}

void	free_p_lst(t_parsed **lst)
{
	t_parsed *current;
	t_parsed *tmp;
	int		i;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		i = 0;
		tmp = current->next;
		while (current->cmd_and_args[i])
		{
			free(current->cmd_and_args[i]);
			i++;
		}
		free(current->cmd_and_args);
		free(current->in);
		free(current->out);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

int	pipe_counter(t_token **tokens)
{
	t_token *current;
	int		pipe_count;

	current = *tokens;
	pipe_count = 0;
	while (current)
	{
		if (current->type == PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count);
}
