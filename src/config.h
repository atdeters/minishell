/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:38 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 10:59:00 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/**
 * 
 * Maybe do a check in the beginning if the colors are valid! Using it wrong
 * here can break the program!
 */
# define SUCC_COLOR "\033[1;32m"
# define FAIL_COLOR "\033[1;91m"
# define CWD_COLOR "\033[1;36m"
# define RESET "\033[0m"

# define GIT_COLOR "\033[1;34m"
# define GIT_COLOR_BRANCH "\033[1;91m"

/**
 * As of now the prompt can only consist out of Ascii Characters
 * Maybe do a check while initializing, because failing to do so can 
 * break the program!
 */
# ifndef PROMPT
#  define PROMPT "vash>"
// #  define PROMPT "\001\➜"
# endif

# ifndef PROMPT_SPACE
#  define PROMPT_SPACE "  "
# endif

# ifndef SHOW_FOLDER
#  define SHOW_FOLDER true
# endif

# ifndef FOLDER_SPACE
#  define FOLDER_SPACE " "
# endif

# ifndef SHOW_GIT
#  define SHOW_GIT true
# endif

# ifndef GIT_LEN_NO_BRANCH
#  define GIT_LEN_NO_BRANCH 7
# endif

# ifndef ANSI_SHELL_LEN
#  define ANSI_SHELL_LEN 8
# endif

# ifndef EMERGENCY_PROMPT
#  define EMERGENCY_PROMPT "vash> "
# endif

#endif