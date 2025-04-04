/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_helpers4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:25:03 by adeters           #+#    #+#             */
/*   Updated: 2025/04/04 16:47:01 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_alias(char *entry)
{
	char	*c;

	c = ft_strrchr(entry, '=') + 1;
	if (count_char(entry, '=') == 1 && *c == '\0')
		return (1);
	return (0);
}

bool	is_valid_entry_form(char *entry)
{
	int	eq_count;
	int	i;

	if (check_empty_alias(entry))
		return (false);
	eq_count = 0;
	i = 0;
	while (entry[i])
	{
		if (entry[i] == '=')
			eq_count++;
		i++;
	}
	if (eq_count < 1)
		return (false);
	return (true);
}

bool	is_unique_key(t_env_lst *lst, char *entry)
{
	char	*key;
	char	*check;
	int		eq_ind;

	if (!lst)
		return (true);
	key = ft_strdup(entry);
	if (!key)
		return (false);
	if (ft_strchr(entry, '='))
	{
		eq_ind = ft_strchr(entry, '=') - entry;
		key[eq_ind] = '\0';
	}
	check = get_value_from_lst(lst, key);
	if (!ft_strcmp(check, key))
		return (free(key), free(check), true);
	return (free(key), free(check), false);
}
