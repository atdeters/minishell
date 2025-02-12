NAME = mini

# Overridable Makros
SHOW_FOLDER		?=	true
SHOW_GIT		?=	true
PROMPT			?=	'"\001\001➜\002\002"'
PROMPT_SPACE	?=	'"  "'
SHOW_EXIT_COL 	?=	true

DEFINES =	-D SHOW_FOLDER=$(SHOW_FOLDER)\
			-D SHOW_GIT=$(SHOW_GIT)\
			-D PROMPT=$(PROMPT)\
			-D PROMPT_SPACE=$(PROMPT_SPACE)\
			-D SHOW_EXIT_COL=$(SHOW_EXIT_COL)

COMP = cc
CFLAGS ?= -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRC_FILES = main.c builtin_cd.c builtin_clear.c builtin_pwd.c init.c\
input.c errors.c env_lst_func.c env_parser.c helpers1.c add_prompts.c\
add_ansi.c get_git.c lexing.c lexing_utils.c lexing_utils_2.c lexing_utils_3.c\
piping.c builtin_echo.c

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

basic: PROMPT='"vash>"'
basic: PROMPT_SPACE='" "'
basic: SHOW_EXIT_COL=false
basic: SHOW_FOLDER=false
basic: SHOW_GIT=false
basic: all

no-werror: CFLAGS=-Wall -Wextra -g
no-werror: all

no-flags: CFLAGS=""
no-flags: all

.PHONY: all clean fclean re tidy basic no-werror no-flags
