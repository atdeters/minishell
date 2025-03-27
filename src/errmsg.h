/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:55:11 by adeters           #+#    #+#             */
/*   Updated: 2025/03/27 15:34:33 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRMSG_H
# define ERRMSG_H

# define SHELL_ERR_IDENT "minishell: "
# define ERR_MSG_FUNC_EXECVE "execve function failed to execute\n"
# define ERR_MSG_FUNC_DUP2 "dup2 function failed to execute\n"
# define ERR_MSG_FUNC_FORK "fork function failed to execute\n"
# define ERR_MSG_FUNC_GETCWD "getcwd function failed to execute\n"
# define ERR_MSG_FUNC_CHDIR "chdir function failed to execute\n"
# define ERR_MSG_ACCESS_FILE ": No such file or directory"
# define ERR_MSG_FUNC_PIPE "pipe function failed to execute\n"
# define ERR_MSG_HIST "history entry could not be added\n"
# define ERR_MSG_ACCESS "command not found: "
# define ERR_MSG_PERM "permission denied: "
# define ERR_MSG_OPEN "could not open file: "
# define EXIT_ERR_IDENT "exit: "
# define ERR_MSG_EXIT_ARGS "exit: too many arguments\n"
# define ERR_MSG_EXIT_NUMS "numeric argument required\n"
# define ERR_MSG_CD_ARGS "cd: too many arguments\n"
# define ERR_MSG_PARSING "parsing error\n"
# define ERR_MSG_SINGLE_QOUTE "parse error near \'\'\'\n"
# define ERR_MSG_DOUBLE_QOUTE "parse error near \'\"\'\n"
# define ERR_MSG_INVALID_PATH "cd: No such file or directory: "
# define ERR_MSG_DIR "Is a directory: "
# define ERR_MSG_VALID_IDENT "Not a valid identifier: "
# define ERR_MSG_INVALID_REDIR "Not a valid redirection\n"

#endif