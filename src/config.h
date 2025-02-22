/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:38 by adeters           #+#    #+#             */
/*   Updated: 2025/02/22 17:43:30 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

// rl_prompt config - PROMPT
# ifndef SUCC_COLOR
/**
 * @brief Color of the prompt `PROMPT` if the option SHOW_EXIT_COL is true and
 * the last exit status is equal to `0`
 */
#  define SUCC_COLOR "\033[1;32m"
# endif

# ifndef FAIL_COLOR
/**
 * @brief Color of the prompt `PROMPT` if the option SHOW_EXIT_COL is true and
 * the last exit status is equal NOT to `0`
 */
#  define FAIL_COLOR "\033[1;91m"
# endif

# ifndef PROMPT
/**
 * @brief Prompt that will be shown for every line within the minishell
 */
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
/**
 * @brief Color of the folder that is shown after the prompt
 * `PROMPT` if the option `SHOW_FOLDER` is true
 */
#  define CWD_COLOR "\033[1;36m"
# endif

# ifndef SHOW_FOLDER
/**
 * @brief Option to show the current working directory after
 * the prompt `PROMPT`. It just displays the last component and not
 * the full path (aka just the folder - not the path to the folder)
 */
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
/**
 * @brief Color of the git signifier that is shown after the prompt
 * `PROMPT` if the option `SHOW_GIT` is true. The branch
 * itself will have the color `GIT_COLOR_BRANCH`
 * 
 * In the format: `git:(branch)` it is the color of the `git:()`
 */
#  define GIT_COLOR "\033[1;34m"
# endif

# ifndef GIT_COLOR_BRANCH
/**
 * @brief Color of the git branch that is shown after the prompt
 * `PROMPT` if the option `SHOW_GIT` is true. The signifier of the git
 * branch will have the color `GIT_COLOR`
 * 
 * In the format: `git:(branch)` it is the color of the `branch`
 */
#  define GIT_COLOR_BRANCH "\033[1;91m"
# endif

# ifndef SHOW_GIT
/**
 * @brief Option to show the current branch after
 * the prompt `PROMPT`.
 * 
 * Format: git:(branch) + GIT_SPACE
 */
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
/**
 * @brief Option to change the prompts color depending on the last exit satus
 * 
 * - If it is true, the color changes to FAIL_COLOR if the exit status != 0
 * and to SUCC_COLOR if it is 0
 * 
 * - If it is false, the color of the prompt `PROMPT` does not change
 */
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