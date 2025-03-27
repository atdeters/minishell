/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:49:03 by andreas           #+#    #+#             */
/*   Updated: 2025/03/27 10:09:45 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_use_alias(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\talias – Create, list, or remove command aliases, allowing ");
	printf("command substitution with support for pipes and redirections.\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\talias [flags] alias[=expansion]\n");
	printf("\n%sFLAGS%s\n", BOLD, RESET);
	printf("\t--remove / -r       Removes an alias (if it already exists)\n");
	printf("\n%sEXAMPLES%s\n", BOLD, RESET);
	printf("\talias               Displays all active aliases\n");
	printf("\talias    [name]     Display the aliases with the");
	printf("corresponding expansion\n");
	printf("\talias -r [name]     Remove a specific alias\n");
	printf("\talias -h            Display this help\n");
	printf("\n%sNOTE%s\n", BOLD, RESET);
	printf("\tIt expects a single command as input.");
	printf("So make sure to format it with quotes.\n");
	printf("\t- 'alias \"st=git status\"' instead of ");
	printf("'alias st=git status' or 'alias st=\"git status\"'\n");
}

void	p_use_echo(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\techo - display a line of text on the standart output\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\techo [FLAGS] [STRING]\n");
	printf("\n%sFLAGS%s\n", BOLD, RESET);
	printf("\t-n                  do not output the trailing newline\n");
}

void	p_use_biman(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\tbiman - display a manual for minishell builtin functions\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\tbiman [builtin name]\n");
}

void	p_use_cd(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\tcd - Change the shell working directory\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\tcd [relative or absolute path to directory]\n");
	printf("\n%sEXAMPLES%s\n", BOLD, RESET);
	printf("\tcd ~                change working directory to home\n");
	printf("\tcd                  change working directory to home\n");
	printf("\tcd ..               moves up one directory\n");
	printf("\tcd ~/minishell      change working directory to the ");
	printf("minishell directory in home\n");
}

void	p_use_env(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\tenv - display environment variables\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\tenv\n");
}
