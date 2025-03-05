/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:02:04 by adeters           #+#    #+#             */
/*   Updated: 2025/03/05 19:16:43 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putstr_fd(ERR_MSG_FUNC_GETCWD, 2);
	else
		printf("%s\n", cwd);
	free(cwd);
}

char	*get_pwd_alloc(t_data *data, bool clean)
{
	char	*tmp;
	char	*cwd;
	char	*cl_buff;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		rage_quit(data, ERR_GETCWD, true, NULL);
	if (clean == true)
	{
		tmp = strrchr(cwd, '/');
		if (tmp)
			tmp++;
		else
			tmp = cwd;
		cl_buff = ft_strdup(tmp);
		if (!cl_buff)
			rage_quit(data, ERR_MALLOC, true, NULL);
		return (free(cwd), cl_buff);
	}
	else
		return (cwd);
}
