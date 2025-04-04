/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_input_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:39:32 by vsenniko          #+#    #+#             */
/*   Updated: 2025/04/04 16:02:58 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_quotes(char *word, char *old_one, char **arr, int n)
{
	int	i;
	int	j;

	i = 0;
	word[i++] = '"';
	j = 0;
	while (old_one[j])
		word[i++] = old_one[j++];
	word[i++] = '"';
	if (arr[n + 1])
		word[i++] = ' ';
	else
		word[i++] = 0;
	word[i] = '\0';
}

static void	free_two_dim(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static char	*ft_strjon_with_freeing(char *s1, char *s2)
{
	char	*final;

	if (!s1)
		return (final = s2, final);
	else
		final = ft_strjoin(s1, s2);
	if (!final)
		return (free(s1), free(s2), NULL);
	free(s1);
	free(s2);
	return (final);
}

int	split_and_add(char **word)
{
	int		i;
	char	*not_final;
	char	**splitted;

	i = 0;
	splitted = ft_split(*word, ' ');
	if (!splitted)
		return (free(*word), 0);
	cool_free(word);
	while (splitted[i])
	{
		not_final = malloc(sizeof(char) * (ft_strlen(splitted[i]) + 4));
		if (!not_final)
			return (free_two_dim(splitted), free(*word), 0);
		add_quotes(not_final, splitted[i], splitted, i);
		i++;
		if (!*word)
			*word = not_final;
		else
			*word = ft_strjon_with_freeing(*word, not_final);
		if (!*word)
			return (free_two_dim(splitted), 0);
	}
	return (free_two_dim(splitted), 1);
}
