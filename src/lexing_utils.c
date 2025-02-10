#include "lexing.h"

int	ft_is_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

t_token	*create_token(token_type type, char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*ft_token_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = ft_token_lstlast(*lst);
	current->next = new;
}

static void	ft_token_lstdelone(t_token *lst)
{
	if (lst == NULL)
		return ;
	if (lst->value)
		free(lst->value);
	free(lst);
}

void	ft_token_lstclear(t_token **lst)
{
	t_token	*current;
	t_token	*tmp;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_token_lstdelone(tmp);
	}
	*lst = NULL;
}