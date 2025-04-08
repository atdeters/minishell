/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:22:10 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/08 14:07:41 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_and_change_flag(char *word, int i, int *flag)
{
	if (word[i] == '\"' && !(*flag))
		*flag = 2;
	else if (word[i] == '\'' && !(*flag))
		*flag = 1;
	else if (word[i] == '\'' && *flag == 1)
		*flag = 0;
	else if (word[i] == '\"' && *flag == 2)
		*flag = 0;
}

static void	transfer_str_in_rq(char *word, char *new_new)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (word[i])
	{
		check_and_change_flag(word, i, &flag);
		if ((word[i] != '\"' && flag == 2) || (word[i] != '\'' && flag == 1)
			|| (word[i] != '\'' && word[i] != '"'))
			new_new[j++] = word[i];
		i++;
	}
	new_new[j] = '\0';
}

char	*remove_quotes(char *word)
{
	int		i;
	char	*new_new;
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	i = 0;
	while (word[i])
	{
		check_and_change_flag(word, i, &flag);
		if ((word[i] != '\"' && flag == 2) || (word[i] != '\'' && flag == 1)
			|| (word[i] != '\"' && word[i] != '\''))
			j++;
		i++;
	}
	new_new = malloc((j + 1) * sizeof(char));
	if (!new_new)
		return (NULL);
	transfer_str_in_rq(word, new_new);
	return (new_new);
}
