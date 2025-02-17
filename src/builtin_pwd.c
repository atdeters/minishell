/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:04 by adeters           #+#    #+#             */
/*   Updated: 2025/02/17 19:28:17 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		printf("getcwd function failed.");
	else
		printf("%s\n", cwd);
	free(cwd);
}

char	*get_pwd_alloc(bool clean)
{
	char	*tmp;
	char	*cwd;
	char	*cl_buff;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	if (clean == true)
	{
		tmp = strrchr(cwd, '/');
		if (tmp)
			tmp++;
		else
			tmp = cwd;
		cl_buff = ft_strdup(tmp);
		return (free(cwd), cl_buff);
	}
	else
		return (cwd);
}
