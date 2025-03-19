NAME = mini

# Config Makros
SHOW_FOLDER		?=	true
SHOW_GIT		?=	true
PROMPT			?=	'"\001\001➜\002\002"'
PROMPT_SPACE	?=	'"  "'
SHOW_EXIT_COL 	?=	true

DEFINES		 =	-D SHOW_FOLDER=$(SHOW_FOLDER)\
				-D SHOW_GIT=$(SHOW_GIT)\
				-D PROMPT=$(PROMPT)\
				-D PROMPT_SPACE=$(PROMPT_SPACE)\
				-D SHOW_EXIT_COL=$(SHOW_EXIT_COL)

COMP		=	cc
CFLAGS		?=	-Wall -Wextra -Werror -g
LDFLAGS		=	-lreadline

SRC_FILES	=	builtin_cd.c builtin_pwd.c builtin_env.c init_com.c init_prog.c get_here_doc_fd.c builtin_alias_helpers3.c ask_user.c builtin_export.c\
				input.c errors.c env_lst_func.c env_parser.c helpers1.c add_rl_prompt.c builtin_alias.c rage_quit.c print_usage.c builtin_unset.c\
				get_git.c lexing.c lexing_utils.c lexing_utils_2.c lexing_utils_3.c builtin_exit.c builtin_alias_helpers2.c builtin_alias_flags.c\
				piping.c builtin_echo.c history.c parser_utils_1.c parser_utils_2.c builtin_alias_helpers.c hdf_arr.c hdf_arr2.c\
				parser.c parser_utils_3.c parser_utils_4.c access.c path.c execution.c free.c free2.c handle_builtins.c main.c env_lst_helpers.c\
				rewrite_input.c env_lst_to_arr.c rewrite_input_utils_1.c mini_flags.c get_fds.c helpers_lst.c debug.c helpers2.c builtin_alias_helpers4.c\
				sig_handler.c hdf_error.c\

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

basic: PROMPT='"msh>"'
basic: PROMPT_SPACE='" "'
basic: SHOW_EXIT_COL=false
basic: SHOW_FOLDER=false
basic: SHOW_GIT=false
basic: all

nw: CFLAGS=-Wall -Wextra -g
nw: all

nf: CFLAGS=""
nf: all

.PHONY: all clean fclean re tidy basic nw nf
