/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:22:10 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/08 13:43:52 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	transfer_str_in_rq(char *word, int flag, char *new_new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if ((word[i] != '\"' && flag == 2) || (word[i] != '\'' && flag == 1)
				|| (word[i] != '\'' && word[i] != '"'))
			new_new[j++] = word[i];
		i++;
	}
	new_new[j] = '\0';
}

static void	change_flag(char *word, int *flag)
{
	int	i;
	
	i = 0;
	while (word[i])
	{
		if (word[i] == '\"' && !(*flag))
			*flag = 2;
		else if (word[i] == '\'' && !(*flag))
			*flag = 1;
		i++;
	}
}

char	*remove_quotes(char *word)
{
	int		i;
	char	*new_new;
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	change_flag(word, &flag);
	i = 0;
	while (word[i])
	{
		if ((word[i] != '\"' && flag == 2) || (word[i] != '\'' && flag == 1)
				|| (word[i] != '\"' && word[i] != '\''))
			j++;
		i++;
	}
	new_new = malloc((j + 1) * sizeof(char));
	if (!new_new)
		return (NULL);
	transfer_str_in_rq(word, flag, new_new);
	return (new_new);
}
