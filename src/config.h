/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:38 by adeters           #+#    #+#             */
/*   Updated: 2025/01/25 16:50:31 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define SUCC_COLOR "\033[1;32m"
# define FAIL_COLOR "\033[1;91m"
# define CWD_COLOR "\033[1;36m"
# define RESET "\033[0m"

# ifndef PROMPT
#  define PROMPT "➜"
# endif

# ifndef SHOW_FOLDER
#  define SHOW_FOLDER true
# endif

#endif