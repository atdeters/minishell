/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:16:12 by vsenniko          #+#    #+#             */
/*   Updated: 2025/01/27 17:30:42 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/libft/libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlen(const char *str);

typedef struct sd_list
{
	char			*content;
	struct sd_list	*prev;
	struct sd_list	*next;
}					t_dlist;

t_dlist				*ft_dlstnew(char *content);
void				ft_dlstadd_front(t_dlist **lst, t_dlist *new);
t_dlist				*ft_dlstlast(t_dlist *lst);
void				ft_dlstadd_back(t_dlist **lst, t_dlist *new);
int					ft_dlstsize(t_dlist *lst);
void				ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void				ft_dlstclear(t_dlist **lst, void (*del)(void *));

#endif