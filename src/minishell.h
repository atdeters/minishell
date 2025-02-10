/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:17 by adeters           #+#    #+#             */
/*   Updated: 2025/02/01 20:34:06 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//// LIBRARIES
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//// HEADERFILES
# include "./libft/libft.h"
# include "config.h"
# include "lexing/lexing.h"

//// ENUMS
enum					e_errors
{
	/**
		* @brief Minishell failed to initialize
		*/
	INIT = 1,
};

//// STRUCTS

typedef struct s_env_lst
{
	char				*filed;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_data
{
	/**
		* @brief Input that has been read from the terminal
		*/
	char				*input;
	/**
		* @brief Exit status of the most recent call
		*
		* Initialized to 0.
		*/
	int					exit_status;
	/**
		* @brief Integer that can be set to a specific error code
		* in case something fails
		*/
	int					error;
	/**
		* @brief If the pwd is a git repository, this one shows the branch
		* If the pwd is not a git repository it with be NULL
		*/
	char				*branch;
	t_env_lst			*env_lst;
	// return after parsing
	char				**prompt;

}						t_data;

//// FUNCTION-FILES
// add_ansi.c
void					start_ansi(char *rl_prompt, char *color);
void					add_ansi(char *rl_prompt, char *color);

// add_prompts.c
void					add_prompt(t_data *data, char *rl_prompt);
int						add_folder(char *rl_prompt);
int						add_git(char *rl_prompt);
int						add_git2(char *path, char *rl_prompt);
void					add_branch(char *line, char *rl_prompt);

// builtin_clear.c
void					clear(void);

// builtin_pwd.c
void					pwd(void);
int						get_pwd(char buff[PATH_MAX], bool clean);

// errors.c
int						p_err(int code);

// helpers1.c
int						count_slash(char *path);
/**
 * Unsafe version of a strlcat. Just protect before the use if needed.
 */
int						ft_strcat(char *dst, const char *src);
char					*allo_strcat(const char *s1, const char *s2);
/**
 * @brief Removes the newline character (`\n`) from the end of a string,
 * if present.
 *        This allows `count_lines` to function
 * correctly regardless of whether the
 *        map file ends with a newline character.
 *
 * @param str The string from which to remove
 * the newline character.
 *
 * @return A pointer to the modified string with any
 * trailing newline replaced by `\0`.
 */
char					*rid_of_nl(char *str);
int						ft_strcpy(char *dest, const char *src);

// init.c
int						init_shell(t_data *data);

// input.c
/**
 * The functions in here a built in a way, that the program does not
 * stop if anything fails in between but it will still have no leaks 
 * or segmentation faulty. The prompt will display incorrectly, but
 * the program is still going to run properly so there is no need to 
 * terminate it.
 */
char					*get_input(t_data *data);

// env_lst_funcs
t_env_lst				*ft_env_lstnew(char *f, char *v);
t_env_lst				*ft_env_lstlast(t_env_lst *lst);
void					ft_env_lstadd_back(t_env_lst **lst, t_env_lst *new);
void					ft_env_lstdelone(t_env_lst *lst);
void					ft_env_lstclear(t_env_lst **lst);

// env_parser
void					parse_env(t_data *data, char **env);

#endif