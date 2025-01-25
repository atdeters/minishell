# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeters <adeters@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/08 16:34:00 by adeters           #+#    #+#              #
#    Updated: 2025/01/14 18:45:30 by adeters          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMP = cc

FLAGS = -Wall -Werror -Wextra

SRCS_LIBFT =	libft/ft_atoi.c libft/ft_itoa.c libft/ft_bzero.c libft/ft_calloc.c\
				libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c\
				libft/ft_isdigit.c libft/ft_isprint.c libft/ft_memchr.c\
				libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c\
				libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c\
				libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c\
				libft/ft_substr.c libft/ft_strchr.c libft/ft_strdup.c\
				libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c\
				libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c\
				libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c\
				libft/ft_strtrim.c libft/ft_tolower.c libft/ft_toupper.c\
				libft/ft_str_tolower.c libft/ft_str_toupper.c libft/ft_lstadd_back.c\
				libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c\
				libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c\
				libft/ft_lstnew.c libft/ft_lstsize.c
SRCS_PRINTF =	ft_printf/ft_count_bytes.c ft_printf/ft_printf.c ft_printf/ft_putchars_fd.c\
				ft_printf/ft_puthexas_fd.c ft_printf/ft_puthexaident_fd.c\
				ft_printf/ft_putnbr_base_fd.c ft_printf/ft_putnumbers_fd.c\
				ft_printf/ft_putstr_fd_retbytes.c ft_printf/ft_putunbr_fd.c ft_printf/ft_fprintf.c
SRCS_GNL	=	get_next_line/get_next_line.c

OBJS = $(SRCS_LIBFT:.c=.o) $(SRCS_PRINTF:.c=.o) $(SRCS_GNL:.c=.o)

MAKEFLAGS = --jobs

%.o: %.c
	@$(COMP) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
