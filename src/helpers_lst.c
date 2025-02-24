/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:20:41 by adeters           #+#    #+#             */
/*   Updated: 2025/02/24 13:56:10 by adeters          ###   ########.fr       */
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

	fields = 0;
	i = -1;
	while (lst1 && lst1[i++])
		fields++;
	i = -1;
	while (lst2 && lst2[i++])
		fields++;
	new = malloc((fields - 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (lst1 && lst1[i])
		new[j++] = strdup(lst1[i++]);
	i = 0;
	while (lst2 && lst2[i])
		new[j++] = strdup(lst2[i++]);
	new[j] = NULL;
	return (new);
}
