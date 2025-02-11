/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:38 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 16:39:00 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

// rl_prompt config - PROMPT
# ifndef SUCC_COLOR
#  define SUCC_COLOR "\033[1;32m"
# endif

# ifndef FAIL_COLOR
#  define FAIL_COLOR "\033[1;91m"
# endif

# ifndef PROMPT
#  define PROMPT "\001\001➜\002\002"
# endif

# ifndef PROMPT_SPACE
/**
 * @brief Spaces after the prompt "PROMPT" in the rl_prompt
 * 
 */
#  define PROMPT_SPACE "  "
# endif

// rl_prompt config - FOLDER
# ifndef CWD_COLOR
#  define CWD_COLOR "\033[1;36m"
# endif

# ifndef SHOW_FOLDER
#  define SHOW_FOLDER true
# endif

# ifndef FOLDER_SPACE
/**
 * @brief Spaces after the folder in the rl_prompt
 * 
 */
#  define FOLDER_SPACE " "
# endif

// rl_prompt config - GIT
# ifndef GIT_COLOR
#  define GIT_COLOR "\033[1;34m"
# endif

# ifndef GIT_COLOR_BRANCH
#  define GIT_COLOR_BRANCH "\033[1;91m"
# endif

# ifndef SHOW_GIT
#  define SHOW_GIT true
# endif

# ifndef GIT_SPACE
/**
 * @brief Spaces after the git branch in the rl_prompt
 * 
 */
#  define GIT_SPACE " "
# endif

/**
 * @brief Base length of the git prompt segment, excluding the branch name.
 * 
 * This constant defines the number of fixed characters in the git prompt
 * (e.g., brackets, spacing, and git indicator symbols) that are always
 * present regardless of the branch name. The actual branch name length
 * must be added to this value to calculate the total git prompt length.
 * 
 * Example: If the git prompt format is "git:(branch)", this constant
 * would be 7 to account for "git:(" and ")".
 * 
 * As this format is currently hardcoded into the program and can not be
 * changed in the config this value should not be changed. It could lead
 * to memory allocation fails otherwise
 */
# define GIT_LEN_NO_BRANCH 6

// global stuff
/**
 * @brief Resets the colors/formatting of the terminal output
 */
# define RESET "\033[0m"

# ifndef SHOW_EXIT_COL
#  define SHOW_EXIT_COL true
# endif

/**
 * @brief Length of the readline non-printing character markers that
 * encapsulate ANSI escape sequences.
 * 
 * In readline, ANSI escape sequences (used for colors/formatting) must be
 * wrapped with "\001" (RL_PROMPT_START_IGNORE) and "\002" 
 * (RL_PROMPT_END_IGNORE) to indicate they are non-printing characters. 
 * This ensures readline correctly calculates the visible prompt length for
 * line wrapping.
 * 
 * This macro defines the total length of these marker characters 
 * (4 bytes each, totaling 8 bytes) for memory allocation purposes.
 */
# define ANSI_SHELL_LEN 8

# ifndef EMERGENCY_PROMPT
/**
 * @brief Fallback prompt used when the standard prompt generation fails.
 * 
 * This simple, static prompt serves as a safety mechanism to ensure
 * the shell remains operational even if prompt customization fails
 * (e.g. memory allocation failures).
 * 
 * Using this fallback prevents non-critical prompt errors from
 * crashing the shell.
 */
#  define EMERGENCY_PROMPT "vash> "
# endif

#endif