/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:08:04 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/12 21:08:08 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	IN,
	OUT,
	HEREDOC,
	APPEND,
	AND,
	PIPE,
	OR,
	LPR,
	RPR,
	STR,
	END
}						t_token;

typedef struct t_redir
{
	t_token				tok;
	char				*file;
	int					flag;
	int					fd;
	struct t_redir		*left;
	struct t_redir		*right;
}						t_redir;

typedef struct t_input
{
	t_token				tok;
	char				*command;
	char				**cmd;
	int					token_flag;
	struct t_input		*left;
	struct t_input		*right;
	t_redir				*redirections;
}						t_input;

typedef struct t_garbage
{
	char				*ptr;
	struct t_garbage	*next;
}						t_garbage;

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
	t_garbage			*garbage;
}						t_g_global;

extern t_g_global		g_global;

t_token					return_token(char c1, char c2);
char					*process_word(char *word);
int						handle_env_var(char **word, int i);
int						handle_dollar_sign(char **word, int i, char quote);
char					get_quote_state(char c, char curr_quote);
char					*join_words(char **words);
int						handle_numeric(char **word, int i);
int						handle_exit_status(char **word, int i);
t_garbage				*ft_lstnew_garbage(void *ptr);
void					ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new);
void					*ft_malloc(int size);
char					*replace_substring(char *str, int start, int len,
							char *new_str);
void					handle_quit(int signum);
void					handle_heredoc(int sig);

int						ft_isspace(char c);
int						ft_strlen_no_space(char *str);

void					exec_and(t_input *input);
void					exec_or(t_input *input);

char					*check_expand_herdoc(char *input);
char					*ft_strjoin_three(char *s1, char *s2, char *s3);

int						check_beggining(char *str);
void					default_signal(void);

char					**parsing_cmd(char *str);
void					delete_quotes(char **args);
char					*new_cmd(char *s, int *flg);
int						calc_len(char *s);
void					should_expnd(int *flg);
void					expand_real(t_input *input);
void					free_garbage(void);

char					*check_expand(char *input);
char					**parsing_cmd(char *str);
void					delete_quotes(char **args);
char					*new_cmd(char *s, int *flg);
int						calc_len(char *s);
void					should_expnd(int *flg);
void					sig_handler(int signum);
void					exec_and(t_input *input);
void					ft_initialize(char **env, int *fd_input,
							int *fd_output);
void					ft_initialize_env(char **env);
void					save_input_output(int *fd_input, int *fd_output);
t_input					*ft_parse(char *rl);
int						token_1(t_input **head, char *s, int *i, int *par);
t_input					*node_creation_cmd(char *s, t_redir *redir, t_token tok,
							int token_flag);
int						check_syntax_error(t_token tok, char *s);
int						check_syntax_help(t_token tok, t_token next);
int						check_spaces(char c);
int						check_rpr(char *s, int i);
int						check_not_operator(t_token tok);
int						return_token_syntax(int tok, char *s, int *i, int *par);
t_input					*token_2(char *s, int *i, t_token tok);
int						build_command_list(t_input **head, t_input *add);
t_input					*list_to_tree(t_input *root);
void					remove_top(t_input **tok_s);
void					push_2(t_input **top, t_input *to_add);
void					push(t_input **a_input, t_input **b_input, int flag);
t_input					*organizer(t_input **input);
void					the_organizer(t_input **input, t_input **tok_stack,
							t_input **new_stack);
int						handle_double_quotes(const char *str, int *i);
int						token_1(t_input **head, char *s, int *i, int *par);
int						build_command_list(t_input **head, t_input *add);
int						check_syntax_help(t_token tok, t_token next);
int						check_spaces(char c);
int						check_rpr(char *s, int i);
int						check_not_operator(t_token tok);
int						check_command(t_token tok);
void					incre(char *s, int *i);
int						str_len(char *s, int i, int flag);
int						choose_str(char c, int flag);
char					**prep_cmd(char *s, int *i, int flag, t_token tok);
char					**fill_command(char *s, int l, int *k, int flag);
char					*cmd_help(char *s, int l, int *k, int flag);
void					check_flag(int flag, char *s, int *k);
int						check_next_quote(char *s, char c);
int						check_syntax(t_token tok, char *s);
int						build_redir_list(t_redir **head, t_redir *add);
int						check_true(t_token tok);
t_redir					*node_create_redirection(char **s, t_token tok);
int						handle_single_quotes(const char *str, int *i);
int						ft_execute(t_input *input);
int						exec_str(t_input *input);
int						expand(t_input *input);
char					**parsing_cmd(char *str);
int						find_len(char *str);
int						look_for_1_quote(char *str, int *i, char c);
char					*ft_getenv(char *s);
int						is_legit(int c);
char					*get_env_value(char *name);
void					fill_between_quote_1(char **str, char *s, int *i);
int						builtins(char **cmd);
int						cd(char **cmd);
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
int						single_pipe(t_input *input);
int						pwd(void);
int						redirections(t_input *input);
int						env_cmp(const char *str1, const char *str2);
int						strcount(char **cmd);
int						unset(char **cmd);
int						ft_ncmp(const char *str1, const char *str2, int n);
int						find_char(char *s, char c);
int						in_out_files(t_input *input);
int						redi_in(t_input *input);
int						check_heredoc(t_input *input);
int						ft_exited(int d, int exit);
char					**fill_command(char *s, int l, int *k, int flag);
void					delete_quotes(char **args);
char					*new_cmd(char *s, int *flg);
void					should_expnd(int *flg);
int						calc_len(char *s);
int						open_heredoc(t_redir *tmp);
int						ft_exit(char **cmd);
int						path_check(char *str);
int						help(char **cmd);
int						find_path(char **cmd);
int						cmd_execution(char **cmd);
int						utils2(char **cmd);
int						red_utils1_in(t_redir *tmp);
int						red_utils2_out(t_redir *tmp);
int						red_utils3_append(t_redir *tmp);
int						utils1(char **cmd);
int						do_direct(int fd, int dest);	
void					handle_interrupt(int sig);
t_input					*creat_node_command(char *s, t_redir *redir,
							t_token tok, int token_flag);
void					handle_signals(int sig);

#endif
