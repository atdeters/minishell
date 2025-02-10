#ifndef LEXING_H
# define LEXING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libft/libft.h"

//STRUCTS & ENUMS
typedef enum e_token_type{
	WORD,
	SINGLE_QOUTE,
	DOUBLE_QOUTE,
	DOLAR_SIGN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
}  token_type;

typedef struct s_token
{
	enum e_token_type type;
	char *value;
	struct s_token *next;
} t_token;

//UTILS FUNCS
int		ft_is_space(char ch);
t_token	*create_token(token_type type, char *value);
t_token	*ft_token_lstlast(t_token *lst);
void	ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **lst);
int	handle_special_char(char *input, t_token **current, int *i);
int	handle_single_quote(int *i, char *input, t_token **current);
int	handle_nested_double_quotes(int *i, char *input, t_token **current);
int	handle_double_quotes(int *i, char *input, t_token **current);
int	handle_word(int *i, char *input, t_token **current);
int	lexing(char *input, t_token **list);
#endif