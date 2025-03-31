NAME = minishell

# Config Makros
SHOW_FOLDER		?=	false
SHOW_GIT		?=	false
PROMPT			?=	'"msh>"'
PROMPT_SPACE	?=	'" "'
SHOW_EXIT_COL 	?=	false

DEFINES		 =	-D PROMPT=$(PROMPT)\
 				-D PROMPT_SPACE=$(PROMPT_SPACE)\
				-D SHOW_FOLDER=$(SHOW_FOLDER)\
				-D SHOW_GIT=$(SHOW_GIT)\
				-D PROMPT=$(PROMPT)\
				-D SHOW_EXIT_COL=$(SHOW_EXIT_COL)

COMP		=	cc
CFLAGS		?=	-Wall -Wextra -Werror -g
LDFLAGS		=	-lreadline -lcurses 

SRC_FILES	=	access.c add_rl_prompt.c builtin_alias.c \
				builtin_alias_flags.c builtin_alias_helpers2.c builtin_alias_helpers3.c \
				builtin_alias_helpers4.c builtin_alias_helpers.c builtin_biman.c \
				builtin_cd.c builtin_echo.c builtin_env.c \
				builtin_exit.c builtin_export.c builtin_pwd.c \
				builtin_unset.c debug.c env_lst_func.c \
				env_lst_helpers.c env_lst_to_arr.c env_parser.c \
				errors.c execution.c free2.c \
				free.c get_fds.c get_git.c \
				get_here_doc_fd.c handle_builtins.c hdf_arr2.c \
				hdf_arr.c hdf_error.c helpers1.c \
				helpers2.c helpers_lst.c history.c \
				init_com.c init_prog.c input.c \
				lexing.c lexing_utils_2.c lexing_utils_3.c \
				lexing_utils.c main.c mini_flags.c \
				parser.c parser_utils_1.c parser_utils_2.c \
				parser_utils_3.c parser_utils_4.c path.c \
				piping.c print_usage2.c print_usage.c \
				rage_quit.c rewrite_input.c rewrite_input_utils_1.c \
				rewrite_input_utils_2.c sig_handler.c rewrite_input_utils_3.c

SRCS = $(addprefix src/, $(SRC_FILES))

OFOLDER = objs
OPATH = objs/
OBJS = $(addprefix $(OPATH), $(SRC_FILES:.c=.o))

ARCH = ./src/libft.a

COLOR = \033[1;32m
RESET = \033[0m

all: $(ARCH) $(NAME)

$(OPATH)%.o: src/%.c
	@mkdir -p $(OFOLDER)
	@$(COMP) $(CFLAGS) $(DEFINES) -c $< -o $@

$(ARCH):
	@make --no-print-directory -C ./src/libft > /dev/null
	@cp ./src/libft/libft.a ./src/libft.a
	@echo "$(COLOR)make: $(ARCH) executed!$(RESET)"

$(NAME): $(OBJS) $(ARCH)
	@$(COMP) $(OBJS) -o $(NAME) $(ARCH) $(LDFLAGS)
	@echo "$(COLOR)make: $(NAME) executed!$(RESET)"

clean:
	@make clean --no-print-directory -C ./src/libft
	@rm -rf $(OFOLDER)
	@rm -rf $(ARCH)
	@rm -rf ./src/libft/libft.a
	@echo "$(COLOR)make: clean executed!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(COLOR)make: fclean executed!$(RESET)"

re: fclean all

tidy: all clean

omg: fclean
	@make --no-print-directory PROMPT="'\"\001\001➜\002\002\"'" PROMPT_SPACE="'\"  \"'" SHOW_EXIT_COL=true SHOW_FOLDER=true SHOW_GIT=true

nf: 
	@make --no-print-directory CFLAGS=""

.PHONY: all clean fclean re tidy basic nw nf
