/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:21:11 by vsenniko          #+#    #+#             */
/*   Updated: 2025/01/28 16:07:56 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// cat cat>
// 01234567

void	clear_exit(t_dlist **lst, char *str)
{
	ft_dlstclear(lst, free);
	printf("%s\n", str);
	exit(1);
}

void	ft_awesome_split(char *str, t_dlist **lst)
{
	int		i;
	t_dlist	*node;
	int		start;
	char	*tmp;

	i = 0;
	printf("str = %s\n", str);
	start = i;
	while (str[i])
	{
		if (str[i] == " " || str[i] == ">" || str[i] == "<" || str[i] == "|")
		{
			tmp = ft_substr(str, start, i - start + 1);
			if (!tmp)
				clear_exit(lst, "allocation in ft_substr failed");
			node = ft_dlstnew(tmp);
			if (!node)
				clear_exit(lst, "allocation for new node failed");
			if (!*lst)
				*lst = node;
			else
				ft_dlstadd_back(lst, node);
		}
	}
}

// cat Makefile>outfile
//["cat", "Makefile", ">", "outfile", \0]
// > < >> << || = ;
//export ARGV=1;
// "ec""ho" smt -> echo smt
// ["echo", "smt", \0]

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*lst;

	if (!env || !*env)
	{
		printf("No env\n");
		exit(1);
	}
	lst = NULL;
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			free(line);
			printf("exit\n");
			exit(0);
		}
		ft_awesome_split(line, &lst);
		printf("%s\n", line);
		add_history(line);
		free(line);
	}
	return (0);
}
