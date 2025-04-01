/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsenniko <vsenniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:17 by adeters           #+#    #+#             */
/*   Updated: 2025/04/01 16:58:35 by vsenniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////* EXT LIBRARIES
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

////* INT LIBRARIES
# include "./libft/libft.h"
# include "config.h"
# include "errmsg.h"

////* MAKROS
# define FD_LIMIT 508
# define MAX_PROCS 1024
# define HIST_FILE_NAME ".msh_history"
# define ALIAS_FILE_NAME ".msh_alias"

////* GLOBAL VARIABLE
extern int				g_signal;

////* ENUMS
enum					e_errors
{
	ERR_EXECVE = 3,
	ERR_DUP2 = 4,
	ERR_FORK = 5,
	ERR_PIPE = 6,
	ERR_HIST = 7,
	ERR_HIST_WFILE = 8,
	ERR_OPEN = 10,
	ERR_USAGE = 11,
	ERR_MALLOC = 12,
	ERR_GNL = 13,
	ERR_CHDIR = 14,
	ERR_INVALID_ENTRY = 15,
	ERR_DUP_ENTRY = 16,
	ERR_GETCWD = 17,
	ERR_BUILTIN_USAGE = 18,
	ERR_INVALID_PATH = 19,
	ERR_ALIAS_INV_RM = 22,
	ERR_INV_BUILTIN = 23,
	ERR_DIR = 24,
	ERR_VALID_IDENT = 25,
	ERR_INVALID_REDIR = 26,
	ERR_NOTDIR = 27,
	ERR_ACCESS_FILE = 28,
	ERR_PERM = 126,
	ERR_ACCESS = 127,
	ERR_PARS = 130,
	ERR_LEXING = 132,
	ERR_PARS_SINGLE_QUTE = 135,
	ERR_PARS_DOUBLE_QUTE = 140,
	ERR_CHILD = 200,
};

enum					e_in_mode
{
	IN_MODE_STD = 0,
	IN_MODE_FILE = 3,
	IN_MODE_PIPE = 4,
	IN_MODE_HERE_DOC = 5,
};

enum					e_out_mode
{
	OUT_MODE_STD = 1,
	OUT_MODE_FILE_TR = 3,
	OUT_MODE_FILE_APP = 5,
	OUT_MODE_PIPE = 4,
};

enum					e_token_type
{
	WORD,
	SINGLE_QOUTE,
	DOUBLE_QOUTE,
	DOLAR_SIGN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	DELIMITER,
	REDIR_APPEND
};

////* STRUCTS
typedef struct s_env_lst
{
	char				*filed;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_parsed
{
	char				**cmd_and_args;
	int					i_c;
	char				**in_arr;
	int					o_c;
	char				**out_arr;
	enum e_in_mode		in_mode;
	enum e_out_mode		out_mode;
	struct s_parsed		*prev;
	struct s_parsed		*next;
}						t_parsed;

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

// TODO: check hist and alias path still needed?
typedef struct s_data
{
	// Scope: Program
	int					exit_status;
	enum e_errors		error;
	bool				flag_single;
	t_env_lst			*env_lst;
	t_env_lst			*alias_lst;
	t_list				*hstlst;
	int					pid[MAX_PROCS];
	int					n_pid;
	char				**envp;
	char				*hist_path;
	char				*alias_path;
	char				*home_path;
	bool				p_err;
	// Scope: Command
	char				*input;
	int					pipe_ind;
	int					pipes_amount;
	int					fd_pipe[FD_LIMIT][2];
	char				**hdf_arr;
	int					hdf_amt;
	t_parsed			*parsed_lst;
	t_token				*token_lst;
	char				*prog_path;
}						t_data;

typedef struct s_pars_data
{
	t_parsed			**parsed_lst;
	int					cmd_amount;
	int					in_amount;
	int					out_amount;
	int					parsed_amount;
	t_token				**token_lst;
	t_env_lst			**env_lst;
	t_token				*cur_head;
	t_token				*cur_tail;

}						t_pars_data;

////* FUNCTION-FILES
// access.c
void					check_access_infile(t_data *data, char *filename);
void					check_access_outfile(t_data *data, char *filename);
void					check_access_command(t_data *data, char *command);

// add_rl_prompt.c
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

// builtin_alias_flags.c
bool					has_flag_rm_alias(char **command);

// builtin_alias_helpers.c
void					alias_to_node(t_data *data, char *entry);
int						load_alias_lst(t_data *data, char *path);
void					add_aliases_to_file(t_data *data);

// builtin_alias_helpers2.c
/* More of a env function than an alias helper */
void					remove_env_node(t_env_lst **lst, char *key);
bool					is_valid_entry_form(char *entry);
bool					is_unique_key(t_env_lst *lst, char *entry);
int						check_entry(t_data *data, char *entry);

// builtin_alias_helpers3.c
bool					needs_expand(char *current, t_token *tmp);
int						expand_alias(t_data *data, t_token **lst);
void					print_env_lst(t_env_lst *lst, bool is_export);

// builtin_alias_helpers4.c
bool					is_valid_entry_form(char *entry);
/* More of a env function than an alias helper */
bool					is_unique_key(t_env_lst *lst, char *entry);

// builtin_alias.c
int						load_alias_lst(t_data *data, char *path);
int						ft_alias(t_data *data, char **command);
bool					is_nc_alias(char **command);

// builtin_biman.c
int						p_err_biman_invalid(char **command);
int						ft_biman(char **command);

// builtin_cd.c
/**
 * @brief Changes the working directory
 */
int						ft_cd(t_data *data, char **command);

// builtin_echo.c
int						ft_echo(char **command);

// builtin_env.c
int						ft_env(t_data *data, char **command);

// builtin_exit.c
int						ft_exit(t_data *data, char **command);

// builtin_export.c
int						ft_export(t_data *data, char **command);

// builtin_pwd.c
/**
 * @brief Prints name of current/working directory
 */
int						ft_pwd(t_data *data, char **command);
/**
 * Built so if it fails it cleanly exits the program aka no check
 * needed
 */
char					*get_pwd_alloc(t_data *data, bool clean);

// builtin_unset.c
int						ft_unset(t_data *data, char **command);

// check_overflow.c
int						check_overflow(char *str);

// debug.c
/**
 * @brief Creates a checkpoint in your code and prints an increasing
 * number for everytime that it is called
 */
void					chp(void);
void					print_parsed_data(t_parsed *lst);
void					p_err_src(char *file, int line);

// errors.c
int						setnret(t_data *data, int code);
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
/**
 * @brief Prints errors and adds the argument that caused the error
 */
int						p_err_arg(int code, char *arg);

// execution.c
int						execute(t_data *data);

// free.c
void					fr_lst(char **arr);
void					cool_free(char **ptr);
void					close_all(t_data *data);
void					free_hdf_arr(t_data *data);

// free2.c
/**
 * Stuff to free after every command
 */
void					free_all_com(t_data *data);
/**
 * Stuff to free after exiting
 */
void					free_all_global(t_data *data);

// get_fds.c
int						get_fd_in(t_data *data, int *fd_in);
int						get_fd_out(t_data *data, int *fd_out);
int						get_fds(t_data *data, int *fd_in, int *fd_out);

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
char					*get_git_alloc(t_data *data);

// get_here_doc_fd.c
char					*delimiter_add_nl(char *delimiter_old);
int						add_random_end(char *doc_file, int amount);
// int						get_here_doc_fd(t_data *data, char *delimiter);

// handle_builtins.c
bool					is_builtin(char *name);
bool					handle_nc_builtin(t_data *data, char **command);
/**
 * @brief Checks whether a function is a builtin or not
 *
 * @return
 * - True, if the function is a builtin
 *
 * - False, if the function is not a builtin
 */
bool					handle_builtin(t_data *data, char **command);

// hdf_arr.c
int						hdf_counter(t_data *data, t_token *lst);
char					*hdf_name_gen(t_data *data);
/**
 * @note Does not have to be checked for success as the `rage_quit()` function
 * is called in case of any errors.
 */
int						create_hdf(t_data *data);
void					hdf_prompt(t_data *data, int nb);
char					*hdf_prompt_alloc(t_data *data, int nb);

// hdf_arr2.c
int						fill_hdf(t_data *data, char *hdf, char *delim, int nb);
int						fill_hdf_arr(t_data *data, t_token **lst);

// hdf_error.c
void					p_hdf_int_warn(char *delimiter);

// helpers_lst.c
char					*get_value_from_lst(t_env_lst *lst, char *key);
char					**lst_join(char **lst1, char **lst2);

// helpers1.c
/**
 * @brief Counts the amount of slash (`/`) characters within a string `path`
 *
 * It is used in the `get_git_alloc()` function to know when the current
 * working directory is the home folder
 */
int						count_char(char *path, char c);
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
int						ft_strcmp(const char *s1, const char *s2);

// helpers2.c
bool					is_num_str(char *str);
int						ft_isnum(int c);
bool					lloverflow(const char *str);
long long int			ft_atoll(const char *nptr);
int						count_opts(char **command);

// history.c
/**
 * Loads the history from a specific history file. Nothing happens
 * if this fails as it isn't really that important and nothing
 * else can break if this function doesn't work.
 */
int						load_old_history(char *hist_file_path);
/**
 * Makes a list of history entries for the current session.
 * Before exiting the program these will be written into a
 * specific history file
 */
int						add_full_history(t_data *data);
int						write_hst_file(t_data *data, char *hist_file_path);
int						free_hst_list(t_data *data);

// init_com.c
/**
 * @brief Initializes the mini shell program
 */
int						init_shell(t_data *data, int ac, char **av, char **env);

// init_prog.c
void					set_shlvl(t_data *data, t_env_lst **lst);
void					init_command(t_data *data);
/**
 * @note Does not have to be checked for success as the `rage_quit()` function
 * is called in case of any errors.
 */
int						pipe_maker(t_data *data);

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

// mini_flags.c
bool					is_flag_single(char *flag);
bool					is_flag_help(char *flag);
int						check_flags(t_data *data, int ac, char **av);

// path.c
/**
 * @brief Joins a directory path with an executable name to form a full
 * executable path.
 *
 * This function concatenates `path` and `exe` with a `/` separator in
 * between. If either `path` or `exe` is `NULL`, the function returns `NULL`.
 *
 * Memory is dynamically allocated for the resulting string.
 * The caller is responsible for freeing the returned string.
 *
 * @param path The directory path (e.g., `"/usr/bin"`).
 * @param exe  The executable name (e.g., `"cat"`).
 *
 * @returns A newly allocated string containing `path/exe`
 * (e.g., `"/usr/bin/cat"`), or `NULL` on failure .
 */
char					*join_path_exe(char *path, char *exe);
char					*get_pathstr(t_data *data);
/**
 * @brief Resolves the full path to an executable if it is not already
 * a direct path.
 *
 * If the command is already a direct path (i.e., it contains a `'/'`
 * character), the function returns the `command` array unchanged.
 * Otherwise, it searches for the executable in the directories specified
 * by the `PATH` environment variable.
 *
 * If the executable is found, `command[0]` is replaced with a newly allocated
 * string containing the full path. The original `command[0]` is freed before
 * replacement, ensuring no additional memory is allocated overall.
 *
 * Example:
 *
 * - Before: `command[0] = "cat";`
 *
 * - After:  `command[0] = "/usr/bin/cat";`
 *
 * @param command A null-terminated string array where the first element
 * represents the executable to resolve.
 *
 * @returns The modified `command` array with `command[0]` updated if
 * necessary or `NULL` in case of an error.
 *
 * @note
 *
 * - The caller remains responsible for freeing `command[0]` as before.
 * This function does not allocate extra memory beyond replacing `command[0]`.
 *
 * - No checks about the accessibility of the executables is done in
 * this function
 */
char					*add_path(t_data *data, char **command);

// piping.c
/**
 * Redirects the fd_in to STDIN and fd_out to STDOUT.
 * If fd_in is equal to STDIN or fd_out is equal to STDOUT,
 * they will do nothing. It closes all open pipes afterwards
 */
int						wait_all(t_data *data);
int						cool_dup(t_data *data, int fd_in, int fd_out);

//* print_usage.c
/**
 * @brief Displays the manual page for the built-in `alias` command.
 */
void					p_use_alias(void);
/**
 * @brief Displays the manual page for the built-in `echo` command.
 */
void					p_use_echo(void);
/**
 * @brief Displays the manual page for the built-in `biman` command.
 */
void					p_use_biman(void);
/**
 * @brief Displays the manual page for the built-in `cd` command.
 */
void					p_use_cd(void);
/**
 * @brief Displays the manual page for the built-in `env` command.
 */
void					p_use_env(void);

//* print_usage2.c
/**
 * @brief Displays the manual page for the built-in `exit` command.
 */
void					p_use_exit(void);
/**
 * @brief Displays the manual page for the built-in `export` command.
 */
void					p_use_export(void);
/**
 * @brief Displays the manual page for the built-in `pwd` command.
 */
void					p_use_pwd(void);
/**
 * @brief Displays the manual page for the built-in `unset` command.
 */
void					p_use_unset(void);
/**
 * @brief Displays the manual page for the minishell program.
 */
void					p_use_msh(void);

// pwd_envs.c
void					replace_pwd_env(t_data *data);

// rage_quit.c
void					rage_quit(t_data *data, int exit_code, bool write_hist,
							char *err_cmd);

//* sig_handler.c
/**
 * @brief Handles the SIGINT signal during here-document creation.
 *
 * This function is called when the SIGINT signal is received during the
 * creation of a here-document. It sets a global signal flag, resets
 * the readline input, and inserts a newline character into the input
 * buffer to exit the readline function.
 *
 * @param signum The signal number (expected to be SIGINT).
 */
void					sig_handle_here_doc(int signum);
/**
 * @brief Default SIGINT signal handler in interactive mode.
 *
 * This function is called when the SIGINT signal is received in interactive
 * mode. It writes a newline, resets the readline input, triggers a reprompt,
 * and frees allocated resources before displaying the shell prompt again.
 *
 * @param signum The signal number (expected to be SIGINT).
 */
void					sig_handle_basic(int signum);
/**
 * @brief Retrieves or sets the static pointer to the shell data.
 *
 * This function returns the static pointer to the shell's data structure.
 * If a non-NULL `data` argument is provided, it updates the pointer to
 * reference the new data. It is used in the signal handler to access or
 * modify the shell's data.
 *
 * @param data A pointer to the shell's data structure
 * (or NULL to retrieve the current pointer).
 * @return The current pointer to the shell's data structure.
 */
t_data					*pointer_to_data(t_data *data);

// replace input $
int						check_replace_input(t_data *data);
int						quotes_problem(t_data *data);
int						in_single_qoute(int pos, char *input);
int						pipe_problem(t_data *data);
int						expand_env_var(t_data *data, char **input);
int						special_case_pid(char **word);
int						check_for_triple(char *input);
int						split_and_add(char **word);

// env func
void					parse_env(t_data *data, char **env);
char					*return_from_env_with_data(t_data *data, char *field);
int						del_env_var(t_env_lst *lst, char *field);
int						parser_env_into_arr(t_data *data);

// env_utils
t_env_lst				*ft_env_lstnew(char *f, char *v);
t_env_lst				*ft_env_lstlast(t_env_lst *lst);
void					ft_env_lstadd_back(t_env_lst **lst, t_env_lst *new);
void					ft_env_lstdelone(t_env_lst *lst);
void					ft_env_lstclear(t_env_lst **lst);
void					ft_env_lstdel_node(t_env_lst *lst, char *field);
int						count_env_list_nodes(t_env_lst *lst);
void					swap_env_nodes(t_env_lst *node1, t_env_lst *node2);
void					sort_env_list(t_env_lst **lst);
void					transfer_into_node(char *str, t_data *data, int j);

// parser functions
int						parser_main(t_data *data);
int						call_check_type(t_pars_data *pars_data, t_parsed *new);
void					init_pars_data(t_pars_data *pars_data, t_data *data,
							t_token **tokens);
int						check_for_count(t_token *token);
int						check_for_putting_words(t_token *token);
char					*return_from_env(t_pars_data pars_data, char *field);
int						parse_in_out(t_token *current, t_parsed **new,
							t_data *data);
int						parse_in_out_part_2(t_token *current, t_parsed **new,
							t_data *data);

// parser utils functions
t_parsed				*create_p_node(char **cmd_and_args, char *in,
							char *out);
void					add_p_back(t_parsed **lst, t_parsed *new);
void					free_p_node(t_parsed *node);
void					free_p_lst(t_parsed **lst);
int						pipe_counter(t_token **tokens);

// lexing
/**
 * @brief Main lexical analysis function that tokenizes the input string
 * @param input The input string to tokenize
 * @param list Pointer to the token list head
 * @param data Shell data structure containing error handling info
 * @return 1 on success, 0 on failure with error set in data->error
 */
int						lexing(char *input, t_token **list, t_data *data);
/**
 * @brief Checks if character is a whitespace
 * @param ch Character to check
 * @return 1 if whitespace, 0 otherwise
 */
int						ft_is_space(char ch);
t_token					*create_token(int type, char *value);
t_token					*ft_token_lstlast(t_token *lst);
void					ft_token_lstadd_back(t_token **lst, t_token *new);
void					ft_token_lstdelone(t_token *lst);
void					ft_token_lstclear(t_token **lst);
int						handle_special_char(char *input, t_token **current,
							int *i, t_data *data);
int						handle_single_quote(int *i, char *input,
							t_token **current);
int						handle_nested_double_quotes(int *i, char *input,
							t_token **current);
int						handle_double_quotes(int *i, char *input,
							t_token **current);
int						handle_word(int *i, char *input, t_token **current,
							t_data *data);
int						check_patern(t_data *data);
/**
 * @brief Checks if character at position is part of a word
 * @param i Current position in input
 * @param input Input string
 * @param flag Quote status flag
 * @return true if character is part of word, false otherwise
 */
bool					is_word_char(int i, char *input, int *flag);
int						handle_dolar(char *input, t_token **current, int *i,
							char **word);
/**
 * @brief Handles here-document delimiter token
 * @param data Shell data structure
 * @param current Pointer to store created token
 * @param i Current position in input
 * @param word Pointer to store delimiter word
 * @return 1 on success, 0 on failure
 */
int						handle_delim(t_data *data, t_token **current, int *i,
							char **word);

#endif