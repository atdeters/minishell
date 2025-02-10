/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:18 by vsenniko          #+#    #+#             */
/*   Updated: 2025/02/10 20:00:43 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "libft/libft.h"
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// STRUCTS & ENUMS
enum e_token_type
{
	WORD,
	SINGLE_QOUTE,
	DOUBLE_QOUTE,
	DOLAR_SIGN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
};

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
}						t_token;

// UTILS FUNCS
int						ft_is_space(char ch);
t_token					*create_token(int type, char *value);
t_token					*ft_token_lstlast(t_token *lst);
void					ft_token_lstadd_back(t_token **lst, t_token *new);
void					ft_token_lstclear(t_token **lst);
int						handle_special_char(char *input, t_token **current,
							int *i);
int						handle_single_quote(int *i, char *input,
							t_token **current);
int						handle_nested_double_quotes(int *i, char *input,
							t_token **current);
int						handle_double_quotes(int *i, char *input,
							t_token **current);
int						handle_word(int *i, char *input, t_token **current);
int						lexing(char *input, t_token **list);
#endif