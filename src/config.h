/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:38 by adeters           #+#    #+#             */
/*   Updated: 2025/02/11 12:52:14 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

// rl_prompt config - PROMPT
# define SUCC_COLOR "\033[1;32m"
# define FAIL_COLOR "\033[1;91m"

# ifndef PROMPT
#  define PROMPT "vash>"
# endif

# ifndef PROMPT_SPACE
/**
 * @brief Spaces after the prompt "PROMPT" in the rl_prompt
 * 
 */
#  define PROMPT_SPACE "  "
# endif

// rl_prompt config - FOLDER
# define CWD_COLOR "\033[1;36m"

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
# define GIT_COLOR "\033[1;34m"
# define GIT_COLOR_BRANCH "\033[1;91m"

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

# ifndef GIT_LEN_NO_BRANCH
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
 */
#  define GIT_LEN_NO_BRANCH 6
# endif

// global stuff
# define RESET "\033[0m"

# ifndef ANSI_SHELL_LEN
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
#  define ANSI_SHELL_LEN 8
# endif

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