/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:20:41 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 13:21:38 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_from_lst(t_env_lst *lst, char *key)
{
	t_env_lst	*tmp;
	char		*value;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->filed))
		{
			value = ft_strdup(tmp->value);
			if (!value)
				return (NULL);
			return (value);
		}
		tmp = tmp->next;
	}
	return (key);
}

char **lst_join(char **lst1, char **lst2)
{
	int		fields;
	int		i;
	int		j;
	char	**new;

	if (!lst1 | !lst2)
		return (NULL);
	while (lst1[i++])
		fields++;
	i = 0;
	while (lst2[i++])
		fields++;
	fields++;
	new = malloc(fields * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (lst1[i++])
		new[j++] = lst1[i];
	i = 0;
	while (lst2[i++])
		new[j++] = lst2[i];
	return (new);
}
