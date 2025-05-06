/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:36:47 by adeters           #+#    #+#             */
/*   Updated: 2025/05/06 13:21:13 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_use_exit(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\texit - cause normal process termination\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\texit [exit-code]\n");
	printf("\n%sNOTE%s\n", BOLD, RESET);
	printf("\tWill not print error messages linked to certain error codes\n");
	printf("\tIf no status is given, it exits with the status ");
	printf("of the last executed command.\n");
}

void	p_use_export(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\texport - set the export attribute for variables\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\texport name[=word]\n");
}

void	p_use_pwd(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\tpwd - print name of current/working directory\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\tpwd [flags]\n");
	printf("\n%sFLAGS%s\n", BOLD, RESET);
	printf("\t--clean / -c    only display the current ");
	printf("folder (without path)\n");
}

void	p_use_unset(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\tunset - unset values and attributes of variables\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\tunset [variable]\n");
}

void	p_use_msh(void)
{
	printf("%sNAME%s\n", BOLD, RESET);
	printf("\tminishell - as beautiful as a shell\n");
	printf("\n%sUSAGE%s\n", BOLD, RESET);
	printf("\t./minishell [flags] [command (in single use mode)]\n");
	printf("\n%sFLAGS%s\n", BOLD, RESET);
	printf("\t-- single / -s	Takes as third argument a string including ");
	printf("the command that needs to be executed. ");
	printf("Opens minishell for this single command and exits afterwards\n");
	printf("\t-- help	/ -h	Prints this help file to the STDOUT\n");
}
