// # ifndef PARSER_H
// # define PARSER_H

// #include "lexing.h"
// // #include "minishell.h"

// //structures and enums
// typedef struct s_parsed{
// 	char **cmd_and_args;
// 	char *in;
// 	char *out;
// 	int in_mode;
// 	int out_mode;
// 	struct s_parsed *prev;
// 	struct s_parsed *next;
// } t_parsed;

// typedef struct s_pars_data{
// 	struct t_parsed **parsed_lst;
// 	int cmd_amount;
// 	int	parsed_amount;
// 	struct t_token **token_lst;
// 	struct t_env_lst **env_lst;
// 	struct t_token *cur_head;
// 	struct	t_token *cur_tail;

// } t_pars_data;

// // int	parser(t_token **tokens, t_data *data);
// int	parser_main(t_token **tokens, t_data *data);

// //utils functions
// t_parsed	*create_p_node(char **cmd_and_args, char *in, char *out);
// t_parsed	*get_p_last(t_parsed *lst);
// t_parsed	*add_p_back(t_parsed **lst, t_parsed *new);
// void		free_p_lst(t_parsed **lst);
// int			pipe_counter(t_token **tokens);

// //parser functions
// void	check_type(t_token *head, t_token *tail, int flag, t_parsed **new);
// #endif