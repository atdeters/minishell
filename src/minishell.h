/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:17 by adeters           #+#    #+#             */
/*   Updated: 2025/01/28 16:05:43 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//// LIBRARIES
# include <stdio.h>
# include <linux/limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//// HEADERFILES
# include "config.h"
# include "./libft/libft.h"

//// ENUMS
enum e_errors
{
	/**
	 * @brief Minishell failed to initialize
	 */
	INIT = 1,
};

//// STRUCTS

typedef struct s_env_lst
{
	char	*filed;
	char	*value;
	t_env_lst *next;
}	t_env_lst;


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
	/**
	 * @brief Integer that can be set to a specific error code
	 * in case something fails
	 */
	int		error;
	
	t_env_lst	*env_lst;

	//return after parsing
	char		**prompt;

	
}				t_data;

//// FUNCTION-FILES
// builtin_clear.c
void	clear(void);

// builtin_pwd.c
void	pwd(void);
int		get_pwd(char buff[PATH_MAX], bool clean);

// errors.c
int		p_err(int code);

// init.c
int		init_shell(t_data *data);

// input.c
char	*get_input(t_data *data);

#endif