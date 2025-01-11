#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_torename/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define IN_CHILD 6
# define IN_PARENT 7
# define IN_HEREDOC 8
# define BEFORE_READLINE 9

typedef enum t_token
{
	IN,      // <
	OUT,     // >
	HEREDOC, // <<
	APPEND,  // >>
	AND,     // &&
	PIPE,    // |
	OR,      // ||
	LPR,     // (
	RPR,     // )
	STR,     // string
	END      // end dyal cmd
}						s_token;

typedef struct t_redir
{
	s_token				tok;
	char				*file;
	int					flag;
	int					fd;
	struct t_redir		*left;
	struct t_redir		*right;
}						s_redir;

typedef struct t_input
{
	s_token				tok;
	char				*command;
	char				**cmd;
	int					token_flag;
	struct t_input		*left;
	struct t_input		*right;
	s_redir				*redirections;
}						s_input;

typedef struct t_garbage
{
	char				*ptr;
	struct t_garbage	*next;
}						s_garbage;

typedef struct t_g_global
{
	char				**env_copy;
	char				*path;
	int					status;
	int					wall;
	int					test;
	int					executed;
	int					exited;
	int					in_herdoc;
	s_garbage			*garbage;
}						s_g_global;

extern s_g_global			g_global;

char	*process_word(char *word);
int	handle_env_var(char **word, int i);
int	handle_dollar_sign(char **word, int i, char quote);
char	get_quote_state(char c, char curr_quote);
char	*join_words(char **words);
int	handle_numeric(char **word, int i);
int	handle_exit_status(char **word, int i);
s_garbage				*ft_lstnew_garbage(void *ptr);
void					ft_lstadd_back_garbage(s_garbage **lst, s_garbage *new);
void					*ft_malloc(int size);
char	*replace_substring(char *str, int start, int len, char *new_str);

int						ft_isspace(char c);
int						ft_strlen_no_space(char *str);

void					exec_and(s_input *input);
void					exec_or(s_input *input);

char					*check_expand_herdoc(char *input);
char					*ft_strjoin_three(char *s1, char *s2, char *s3);

void					default_signal(void);

char					**parsing_cmd(char *str);
void					delete_quotes(char **args);
char					*new_cmd(char *s, int *flg);
int						calc_len(char *s);
void					should_expnd(int *flg);
void					expand_real(s_input *input);
void					free_garbage(void);

char					*check_expand(char *input);
// char					**ft_split_diff(char *s, char c);

char					**parsing_cmd(char *str);
void					delete_quotes(char **args);
char					*new_cmd(char *s, int *flg);
int						calc_len(char *s);
void					should_expnd(int *flg);

void					sig_handler(int signum);

void					exec_and(s_input *input);
void					ft_initialize(char **env, int *fd_input,
							int *fd_output);
void					ft_initialize_env(char **env);
void					save_input_output(int *fd_input, int *fd_output);
s_token					return_token(char c1, char c2);
s_input					*ft_parse(char *rl);
int						check_beggining(char *str);
int						token_1(s_input **head, char *s, int *i, int *par);
s_input					*node_creation_cmd(char *s, s_redir *redir, s_token tok,
							int token_flag);
int						check_syntax_error(s_token tok, char *s);
int						check_syntax_help(s_token tok, s_token next);
int						check_spaces(char c);
int						check_rpr(char *s, int i);
int						check_not_operator(s_token tok);
int						return_token_syntax(int tok, char *s, int *i, int *par);
s_input					*token_2(char *s, int *i, s_token tok);
int						build_command_list(s_input **head, s_input *add);
s_input					*list_to_tree(s_input *root);
void					remove_top(s_input **tok_s);
void					push_2(s_input **top, s_input *to_add);
void					push(s_input **a_input, s_input **b_input, int flag);
s_input					*shunting_yard(s_input **input);
void					the_shunting_yard(s_input **input, s_input **tok_stack,
							s_input **new_stack);
int						handle_double_quotes(const char *str, int *i);
int						token_1(s_input **head, char *s, int *i, int *par);
int						build_command_list(s_input **head, s_input *add);
int						check_syntax_help(s_token tok, s_token next);
int						check_spaces(char c);
int						check_rpr(char *s, int i);
int						check_not_operator(s_token tok);
int						check_command(s_token tok);
void					incre(char *s, int *i);
int						str_len(char *s, int i, int flag);
int						choose_str(char c, int flag);
char					**prep_cmd(char *s, int *i, int flag, s_token tok);
char					**fill_command(char *s, int l, int *k, int flag);
char					*cmd_help(char *s, int l, int *k, int flag);
void					check_flag(int flag, char *s, int *k);
int						check_next_quote(char *s, char c);
int						check_syntax(s_token tok, char *s);
int						build_redir_list(s_redir **head, s_redir *add);
int						check_true(s_token tok);
s_redir					*node_create_redirection(char **s, s_token tok);
int						handle_single_quotes(const char *str, int *i);
int						ft_execute(s_input *input);
int						exec_str(s_input *input);
int						expand(s_input *input);
// char					*expand_var(char *str, int *i);
char					**parsing_cmd(char *str);
int						find_len(char *str);
int						look_for_1_quote(char *str, int *i, char c);
// int						length_val(char *str, int *i);
char					*ft_getenv(char *s);
int						is_legit(int c);
char					*get_env_value(char *name);
// char					*parsing_redirection(s_redir *redir, char *str,
							// int *flag);
// void					fill_between_quote_2(char **str, char *s, int *i);
// void					fill_between_quote_2_help(char **str, int *i, char *s);
// void					ft_change_command(char *command, char *str);
// void					change_val(char **keep, char *s, int *i);
void					fill_between_quote_1(char **str, char *s, int *i);
int						builtins(char **cmd);
int						cd(char **cmd);
// void					free_list(char **str);
int						help(char **cmd);
int						find_path(char **cmd);
int						cmd_execution(char **cmd);
int						check_option(char *str);
int						echo(char **cmd);
int						env(char **cmd);
int						join_var(char *var);
int						putstr(char *str);
void					sort_list(int len);
void					copying_II(char *v);
int						var_parser(char *v);
int						check_variable(char *var);
int						export_listing(char **cmd);
int						export(char **cmd);
int						single_pipe(s_input *input);
int						pwd(void);
int						redirections(s_input *input);
int						env_cmp(const char *str1, const char *str2);
int						strcount(char **cmd);
int						unset(char **cmd);
int						ft_ncmp(const char *str1, const char *str2, int n);
int						find_char(char *s, char c);
int						in_out_files(s_input *input);
int						redi_in(s_input *input);
int						check_heredoc(s_input *input);

int						ft_exited(int d, int exit);
char					**fill_command(char *s, int l, int *k, int flag);
void					delete_quotes(char **args);
char					*new_cmd(char *s, int *flg);
void					should_expnd(int *flg);
int						calc_len(char *s);
int						open_heredoc(s_redir *tmp);
int						ft_exit(char **cmd);
void					handle_interrupt(int sig);
s_input					*creat_node_command(char *s, s_redir *redir, s_token tok, int token_flag);
void					handle_signals(int sig);

#endif