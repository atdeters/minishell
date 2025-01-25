/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:04 by adeters           #+#    #+#             */
/*   Updated: 2025/01/25 16:11:11 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		printf("getcwd function failed\n");
}

int	get_pwd(char buff[PATH_MAX], bool clean)
{
	char	*tmp;
	char	cwd[PATH_MAX];
	int		i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	buff = memset(buff, '\0', PATH_MAX);
	if (clean == true)
	{
		tmp = strrchr(cwd, '/');
		if (tmp)
			tmp++;
		else
			tmp = cwd;
	}
	else
		tmp = cwd;
	i = 0;
	while (tmp[i])
	{
		buff[i] = tmp[i];
		i++;
	}
	return (0);
}
