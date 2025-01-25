/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:17 by adeters           #+#    #+#             */
/*   Updated: 2025/01/25 16:50:46 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//// LIBRARIES
# include <stdio.h>
# include <linux/limits.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//// HEADERFILES
# include "config.h"

//// ENUMS

//// STRUCTS
typedef struct s_data
{
	/**
	 * @brief Input that has been read from the terminal
	 */
	char	*input;
	/**
	 * @brief Exit status of the most recent call
	 * 
	 * Initialized to 0.
	 */
	int		exit_status;
}				t_data;

//// FUNCTION-FILES
// builtin_pwd.c
void	pwd(void);
int		get_pwd(char buff[PATH_MAX], bool clean);

// init.c
int		init_shell(t_data *data);

// input.c
char	*get_input(t_data *data);

#endif