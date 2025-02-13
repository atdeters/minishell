/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:55:11 by adeters           #+#    #+#             */
/*   Updated: 2025/02/13 18:56:02 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRMSG_H
# define ERRMSG_H

// global messages
# define VASH_ERR_IDENT "vash:"

// critical errors (program terminates)
# define E_MSG_INIT_PROG "failed to initialize program"
# define E_MSG_INIT_COM "command initialization failed too often"
# define E_MSG_FUNC_EXECVE "execve function failed to execute"
# define E_MSG_FUNC_DUP2 "dup2 function failes to execute"
# define E_MSG_FUNC_FORK "fork function failes to execute"
# define E_MSG_FUNC_FORK "fork function failes to execute"

// non-critical errors (program does not terminate)
# define E_NC_MSG_FUNC_PIPE "pipe could temporarily no be built"
# define E_NC_MSG_HIST "history entry could not be added"

#endif