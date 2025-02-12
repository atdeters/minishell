/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:17 by adeters           #+#    #+#             */
/*   Updated: 2025/02/12 15:19:27 by adeters          ###   ########.fr       */
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
# include <sys/wait.h>

//// HEADERFILES
# include "./libft/libft.h"
# include "config.h"
# include "lexing.h"

//// MAKROS
# define FD_LIMIT 508
// Random number so far; not limited by the FD_LIMIT like in pipex
# define MAX_PROCS 1024

//// ENUMS
enum					e_errors
{
	/**
	 * @brief Minishell failed to initialize
	 */
	INIT_PROG = 1,
	/**
	 * Current command failed to initialize
	 */
	INIT_COM = 2,
	EXEC = 3,
	DUP = 4,
	FORK = 5,
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
	/**
	 * @brief The next pipe that will be opened
	 */
	int					n_pipe;
	/**
	 * Amount of pipes needed for a given command
	 */
	int					pipes_amount;
	/**
	 * 2D Array of maximum possible file descriptors (limited by 
	 * FD_LIMIT).
	 */
	int					fd[FD_LIMIT][2];
	/**
	 * The amount of processes a given command needs to be executed
	 * properly. This defines how often the `fork()` and the `wait_pid()`
	 * function will be called
	 */
	int					processes;
	/**
	 * Array of pids
	 */
	int					pid[MAX_PROCS];
	/**
	 * Next index in the pid array
	 */
	int					n_pid;
	char				**envp;

}						t_data;

//// FUNCTION-FILES
// add_ansi.c
/**
 * @brief Adds ANSI color codes at the `beginning` of a readline prompt with
 * proper escape sequences.
 *
 * @param rl_prompt The readline prompt string to modify
 * @param color The ANSI color code to add to the prompt
 * @return char* Returns the modified prompt string, or NULL if rl_prompt 
 * is NULL
 *
 * This function wraps ANSI color codes with readline's non-printing
 * character markers (\001 and \002) at the beginning of the prompt to 
 * ensure proper line editing behavior. The function modifies the input
 * string directly and also returns it.
 *
 * @warning The rl_prompt parameter must have sufficient space allocated to
 * accommodate the additional characters.
 * 
 * @warning Always use this function at the beginning of the rl_prompt. If
 * something needs to be added to an already existing rl_prompt use the 
 * `add_ansi` function instead!
 */
char					*start_ansi(char *rl_prompt, char *color);
/**
 * @brief Adds ANSI color codes to a readline prompt with proper escape 
 * sequences
 *
 * @param rl_prompt The readline prompt string to modify
 * @param color The ANSI color code to add to the prompt
 * @return char* Returns the modified prompt string, or NULL if rl_prompt 
 * is NULL
 *
 * This function wraps ANSI color codes with readline's non-printing
 * character markers (\001 and \002) to ensure proper line editing behavior.
 * The function modifies the input string directly and also returns it.
 *
 * @warning The rl_prompt parameter must have sufficient space allocated to
 * accommodate the additional characters.
 * 
 * @warning Always use this function to add on to an already existing rl_prompt
 * If something needs to be added to the beginning of a new rl_prompt use the
 * `start_ansi` function instead!
 */
char					*add_ansi(char *rl_prompt, char *color);

// add_prompts.c
/**
 * @brief Adds a prompt to the readline prompt string, with an optional color
 * based on the exit status.
 *
 * @param data A pointer to the data structure containing the exit status
 * @param rl_prompt The readline prompt string to modify
 * @return char* Returns the modified prompt string, or NULL if rl_prompt 
 * is NULL
 *
 * This function checks the exit status and applies a corresponding color
 * (`FAIL_COLOR` or `SUCC_COLOR`) to the beginning of the prompt using the 
 * `start_ansi` function. Then, it appends the prompt and a space
 * to the readline prompt string. The space is defined as `PROMPT_SPACE`
 * and can be changed in the config.h file.
 * 
 * As it uses the `start_ansi` function
 * rather than the `add_ansi` function it is important to always start with
 * this function when creating a new `rl_prompt`
 *
 * @warning The rl_prompt parameter must have sufficient space allocated to
 * accommodate the additional characters.
 */
char					*add_prompt(t_data *data, char *rl_prompt);
/**
 * @brief Adds the current working directory path to the readline prompt
 * with an optional color.
 *
 * @param rl_prompt The readline prompt string to modify
 * @param path The current working directory path to append to the prompt
 * @return char* Returns the modified prompt string, or NULL if rl_prompt 
 * is NULL
 *
 * This function applies a color to the prompt using the `add_ansi` function
 * and appends the specified directory path (the current working directory)
 * to the readline prompt. A space is also added after the path. This space
 * is defined as `FOLDER_SPACE` and can be changed in the config.h file.
 *
 * @note The rl_prompt parameter must have sufficient space allocated to
 * accommodate the additional characters.
 *
 * @warning The function does not check for buffer overflow when concatenating
 * strings.
 */
char					*add_folder(char *rl_prompt, char *path);
/**
 * @brief Adds the current Git branch to the readline prompt, with appropriate
 * colors.
 *
 * @param rl_prompt The readline prompt string to modify
 * @param branch The current Git branch name to append to the prompt
 * @return char* Returns the modified prompt string, or NULL if rl_prompt 
 * is NULL
 *
 * This function applies a color to the prompt using the `add_ansi` function
 * and appends the specified git branch to the readline prompt. A space is 
 * also added after the branch. This space is defined as `GIT_SPACE` and
 * can be changed in the config.h file.
 *
 * The modified prompt could look like:
 *
 * git:(main)(+GIT_SPACE)
 * 
 * @warning The rl_prompt parameter must have sufficient space allocated to
 * accommodate the additional characters.
 * 
 */
char					*add_branch(char *rl_prompt, char *branch);

// builtin_cd.c
/**
 * @brief Changes the working directory
 */
void					cd(char *path);

// builtin_clear.c
/**
 * @brief Clears the terminal screen
 */
void					clear(void);

// builtin_pwd.c
/**
 * @brief Prints name of current/working directory
 */
void					pwd(void);
/**
 * @brief Retrieves a dynamically allocated string containing the current
 * working directory and optionally cleans it.
 * 
 * This function uses `getcwd()` to get the current working directory and
 * returns a dynamically allocated string representing the current directory
 * path. If the `clean` parameter is set to `true`, the function will clean
 * the directory path by extracting the last component (i.e., the folder or
 * file name after the final `/`) and returning it. If `clean` is `false`,
 * the full path is returned.
 * 
 * @param clean A boolean flag that determines whether to return the full path
 * or just the last component.
 *
 *              - If `true`, returns only the last part of the current working
 * directory.
 *
 *              - If `false`, returns the full path.
 * 
 * @return A pointer to the dynamically allocated string containing the desired
 * directory path or component.
 *         - If the `getcwd()` function fails or returns NULL,
 * `NULL` is returned.
 * 
 *         - If `clean` is `true`, a pointer to a newly allocated string with
 * only the last component of the path.
 * 
 *         - If `clean` is `false`,
 * a pointer to the full current directory path.
 * 
 * @note The returned pointer should be freed
 * by the caller to avoid memory leaks.
 */
char					*get_pwd_alloc(bool clean);

// errors.c
/**
 * @brief Handles error reporting based on a given error code.
 * 
 * This function checks the provided error `code` and prints an error message
 * to standard error (`stderr`) based on the value of the code. The function
 * then returns the provided error code to the caller. Ideally this error
 * code is used as exit status of the program.
 * 
 * @param code An integer representing an error code that determines which
 * message is printed. Specific error codes may have predefined messages.
 * Valid error codes are part of the errors enum (`e_errors`)
 * 
 * @return The same error code that was passed as input.
 */
int						p_err(int code);

// get_git.c
/**
 * @brief Retrieves a dynamically allocated string containing the current
 * git branch name from the repository (if pwd is a repository)
 * 
 * This function traverses the directories starting from the current working
 * directory upwards, checking for the presence of a `.git/HEAD` file. 
 * Once the `.git/HEAD` file is found, it reads its contents to extract the
 * reference to the current git branch.
 * 
 * @return A pointer to a dynamically allocated string containing the git
 * branch name, or `NULL` if the directory is not a git repository or
 * an error occurs.
 * 
 * @note The returned branch name is dynamically allocated and must be freed
 * by the caller to avoid memory leaks.
 */
char					*get_git_alloc(void);

// helpers1.c
/**
 * @brief Counts the amount of slash (`/`) characters within a string `path`
 * 
 * It is used in the `get_git_alloc()` function to know when the current
 * working directory is the home folder
 */
int						count_slash(char *path);
/**
 * Unsafe version of a strlcat. Just protect before the use if needed.
 */
int						ft_strcat(char *dst, const char *src);
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
/**
 * @brief `UNSAFE` copying of a string
 * 
 * The `ft_strcpy()` function copies the string pointed to by src,
 * including the terminating null byte (`\0`), to the buffer pointed
 * to by dest.
 * The strings may not overlap, and the destination string dest must
 * be large enough to receive the copy.  Beware of buffer overruns!
 */
int						ft_strcpy(char *dest, const char *src);

// init.c
/**
 * @brief Initializes the mini shell program
 */
int						init_shell(t_data *data, char **env);
int						init_command(t_data *data);

// input.c
/**
 * @brief Retrieves the user input for the shell, constructing a prompt with
 * dynamic elements like the current directory and git branch, and falls back
 * to an emergency prompt if allocation fails.
 * 
 * This function builds the `rl_prompt` dynamically by including configurable
 * components such as the current working directory (if `SHOW_FOLDER=true`)
 * and git branch (if `SHOW_GIT=true`). If the `rl_prompt` allocation fails,
 * the `EMERGENCY_PROMPT` will be used instead, ensuring that the shell remains 
 * operational. It is defined within the `config.h` file.
 * This behavior is designed to avoid segmentation faults, as the prompt
 * elements will simply be omitted in case of failure, without interrupting
 * the shell's operation.
 * 
 * The process includes:
 * 
 * - Allocating memory for the prompt
 * 
 * - Adding the prompt color depending of the last exit status,
 * current directory (if enabled), and git branch (if enabled)
 * 
 * - Handling ANSI escape sequences for prompt formatting
 * 
 * - Falling back to `EMERGENCY_PROMPT` if the prompt allocation fails
 * 
 * @param data A pointer to the `t_data` structure, which holds the exit
 * status and other necessary shell data.
 * 
 * @return A pointer to the user input string or `NULL` if the readline
 * function fails to retrieve user input
 * 
 * @note The function ensures that the shell remains functional even if
 * the prompt components (folder or Git branch) cannot be constructed
 * due to allocation failure.
 * 
 * @warning The returned string (`input`) is dynamically allocated and
 * must be freed by the caller to avoid memory leaks.
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

// piping.c
/**
 * Redirects the fd_in to STDIN and fd_out to STDOUT. If fd_in is equal
 * to STDIN or fd_out is equal to STDOUT, they will do nothing.
 * 
 * It closes all open pipes afterwards
 * 
 */
void					wait_all(t_data *data);
void					close_all(t_data *data);
int						cool_dup(t_data *data, int fd_in, int fd_out);

#endif