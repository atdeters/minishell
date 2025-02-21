NAME = mini

# Overridable Makros
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

MAIN		?=	tests/works_main.c tests/test_parse_dolar.c

SRC_FILES	=	builtin_cd.c builtin_pwd.c builtin_env.c init_com.c init_prog.c\
				input.c errors.c env_lst_func.c env_parser.c helpers1.c add_rl_prompt.c\
				get_git.c lexing.c lexing_utils.c lexing_utils_2.c lexing_utils_3.c\
				piping.c builtin_echo.c history.c parser_utils_1.c parser_utils_2.c\
				parser.c parser_utils_3.c parser_utils_4.c access.c path.c execution.c free.c\
				rewrite_input.c env_lst_to_arr.c rewrite_input_utils_1.c\

SRCS = $(addprefix src/, $(SRC_FILES))

OFOLDER = objs
OPATH = objs/
OBJS = $(addprefix $(OPATH), $(SRC_FILES:.c=.o)) $(MAIN)

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

basic: PROMPT='"vash>"'
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
