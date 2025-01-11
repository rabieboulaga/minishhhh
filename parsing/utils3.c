/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:58:46 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 21:58:49 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_syntax_error(s_token tok, char *s)
{
	s_token	next;

	next = return_token(*s, *(s + 1));
	if (check_syntax_help(tok, next))
		return (1);
	if (next == END)
	{
		ft_putstr_fd("syntax error near unexpected token`newline'\n", 2);
	}
	else if (next == AND || next == OR || next == APPEND || next == HEREDOC)
	{
		ft_putstr_fd("syntax error near unexpected token`", 2);
		ft_putchar_fd(*(s + 1), 2);
		ft_putchar_fd(*(s + 1), 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token`", 2);
		ft_putchar_fd(*s, 2);
		ft_putstr_fd("'\n", 2);
	}
	g_global.exited = 2;
	return (0);
}

int	return_token_syntax(int tok, char *s, int *i, int *par)
{
	(*i)++;
	if (tok == OR || tok == AND || tok == HEREDOC || tok == APPEND)
		(*i)++;
	else if (tok == LPR)
	{
		if (*par == 0)
			*par = *i;
		*par = check_rpr(&s[*par], *par) + 1;
		if (*par == 0)
			return (0);
	}
	else if (tok == RPR && *i > *par)
	{
		ft_putstr_fd("syntax error: unexpected ')'\n", 2);
		g_global.exited = 2;
		return (0);
	}
	while (check_spaces(s[*i]) == 1)
		(*i)++;
	if (!check_syntax_error(tok, &s[*i]))
		return (0);
	return (1);
}

s_input	*creat_node_command(char *s, s_redir *redir, s_token tok,
		int token_flag)
{
	s_input	*node;

	node = ft_malloc(sizeof(s_input));
	if (!node)
	{
		ft_putstr_fd("failes\n", 2);
		exit(1);
	}
	node->command = s;
	node->cmd = NULL;
	node->tok = tok;
	node->token_flag = token_flag;
	node->redirections = redir;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	build_command_list(s_input **head, s_input *add)
{
	s_input	*help;

	if (!head || !add)
		return (0);
	if (!*head)
		*head = add;
	else
	{
		help = *head;
		while (help->right)
			help = help->right;
		help->right = add;
		add->left = help;
	}
	return (1);
}

int	check_command(s_token tok)
{
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (4);
	if (tok == PIPE)
		return (3);
	if (tok == OR || tok == AND)
		return (2);
	return (1);
}
